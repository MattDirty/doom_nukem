/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_mouse_clicks_on2.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfatton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/20 06:17:05 by lfatton           #+#    #+#             */
/*   Updated: 2019/04/20 06:17:07 by lfatton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor_mouse_clicks.h"
#include "editor_panel_buttons.h"
#include "in_which_sector.h"

enum e_bool	click_on_walls(t_editor *ed, t_linked_walls *linked_walls,
		int mouse_x, int mouse_y)
{
	t_linked_walls	*ptr;

	ptr = linked_walls;
	while (ptr->wall)
	{
		if (is_on_seg(ptr->wall->segment, (t_i_coords){mouse_x, mouse_y},
				ed->map_offset, ed->zoom))
		{
			ed->selected.wall = ptr->wall;
			return (e_true);
		}
		ptr = ptr->next;
	}
	return (e_false);
}

enum e_bool	click_on_panel(t_editor *ed, int mouse_x, int mouse_y)
{
	t_buttons	*buttons;

	if (mouse_x < PANEL_X)
		return (e_false);
	buttons = ed->panel.buttons;
	while (buttons)
	{
		if (is_in_rect(&buttons->item.rect, mouse_x, mouse_y))
		{
			buttons->item.f((t_params)buttons->item.params);
			return (e_true);
		}
		buttons = buttons->next;
	}
	clear_selection(&ed->dragged);
	ed->state = e_null;
	return (e_true);
}

enum e_bool	click_on_nodes(t_editor *ed, t_linked_walls *linked_walls,
				int x, int y)
{
	t_linked_walls	*ptr;
	t_rect			rect;

	ptr = linked_walls;
	while (ptr->wall)
	{
		rect = create_rect(ed->map_offset.x + ptr->wall->segment.x1 * ed->zoom
				- CORNER_SIZE / 2, ed->map_offset.y - ptr->wall->segment.y1
				* ed->zoom - CORNER_SIZE / 2, CORNER_SIZE, CORNER_SIZE);
		if (is_in_rect(&rect, x, y))
		{
			deal_with_clicked_node(ed, ptr, (
					t_coords){ptr->wall->segment.x1, ptr->wall->segment.y1});
			return (e_true);
		}
		rect = create_rect(ed->map_offset.x + ptr->wall->segment.x2 * ed->zoom
				- CORNER_SIZE / 2, ed->map_offset.y - ptr->wall->segment.y2
				* ed->zoom - CORNER_SIZE / 2, CORNER_SIZE, CORNER_SIZE);
		if (is_in_rect(&rect, x, y))
		{
			deal_with_clicked_node(ed, ptr, (
					t_coords){ptr->wall->segment.x2, ptr->wall->segment.y2});
			return (e_true);
		}
		ptr = ptr->next;
	}
	return (e_false);
}
