/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_mouse_clicks.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badhont <badhont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/20 05:22:43 by lfatton           #+#    #+#             */
/*   Updated: 2019/04/20 17:35:05 by badhont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "e_bool.h"
#include "editor.h"
#include "editor_draw.h"
#include "editor_walls_nodes.h"
#include "editor_mouse_clicks.h"
#include "editor_panel_buttons.h"
#include "map.h"

void		copy_sector_floor_ceil(t_sector *target, t_sector *source)
{
	target->ceil = source->ceil;
	target->floor = source->floor;
	target->open_sky = source->open_sky;
}

void		deal_with_clicked_sector(t_editor *ed)
{
	(void)ed;
}

void		clear_selection(t_selected_elements *selected)
{
	if (selected->nodes != NULL)
		free_walls_nodes(selected->nodes);
	selected->nodes = NULL;
	selected->p_spawn = NULL;
	selected->enemy = NULL;
	selected->object = NULL;
	selected->sector = NULL;
	selected->wall = NULL;
	selected->pickable = NULL;
}

void		mouseup_action(t_editor *ed, int mouse_x, int mouse_y)
{
	(void)mouse_x;
	(void)mouse_y;
	clear_selection(&ed->dragged);
}

void		mousedown_action(t_editor *ed, int mouse_x, int mouse_y)
{
	if (click_on_panel(ed, mouse_x, mouse_y))
		return ;
	if (ed->state)
	{
		ed->state_func[ed->state](ed, mouse_x, mouse_y);
		return ;
	}
	clear_selection(&ed->selected);
	free_buttons_list(ed->panel.buttons);
	ed->panel.buttons = NULL;
	clear_selection(&ed->dragged);
	if (click_on_player(ed, ed->map, mouse_x, mouse_y))
		return ;
	if (click_on_enemy(ed, ed->map, mouse_x, mouse_y))
		return ;
	if (click_on_pickable(ed, ed->map, mouse_x, mouse_y))
		return ;
	if (click_on_object(ed, ed->map, mouse_x, mouse_y))
		return ;
	if (click_on_nodes(ed, ed->linked_walls, mouse_x, mouse_y))
		return ;
	if (click_on_walls(ed, ed->linked_walls, mouse_x, mouse_y))
		return ;
	if (click_on_sector(ed, ed->map, mouse_x, mouse_y))
		return ;
}
