/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_mouse_clicks_on.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfatton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/20 06:09:42 by lfatton           #+#    #+#             */
/*   Updated: 2019/04/20 06:09:43 by lfatton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor_mouse_clicks.h"
#include "editor_panel_buttons.h"
#include "in_which_sector.h"

enum e_bool	click_on_sector(t_editor *ed, t_map *map, int mouse_x, int mouse_y)
{
	ed->selected.sector = in_which_sector(
			(t_coords){
				((double)mouse_x - ed->map_offset.x) / ed->zoom,
				((double)-mouse_y + ed->map_offset.y) / ed->zoom},
			map->sectors);
	if (!ed->selected.sector)
		return (e_false);
	deal_with_clicked_sector(ed);
	return (e_true);
}

enum e_bool	click_on_player(t_editor *ed, t_map *map, int x, int y)
{
	t_rect	rect;

	rect = create_rect(ed->map_offset.x + map->spawn.x * ed->zoom - 10,
			ed->map_offset.y - map->spawn.y * ed->zoom - 10, 20, 20);
	if (is_in_rect(&rect, x, y))
	{
		deal_with_clicked_player(ed, &map->spawn);
		return (e_true);
	}
	return (e_false);
}

enum e_bool	click_on_object(t_editor *ed, t_map *map, int mouse_x, int mouse_y)
{
	int			i;
	int			j;
	t_sector	*sector;
	t_rect		rect;

	i = -1;
	while (++i < map->sectors->count)
	{
		sector = map->sectors->items[i];
		j = -1;
		while (++j < sector->objects->count)
		{
			rect = create_rect(
					ed->map_offset.x + sector->objects->items[j].x * ed->zoom
					- 6, ed->map_offset.y - sector->objects->items[j].y
					* ed->zoom - 6, 12, 12);
			if (is_in_rect(&rect, mouse_x, mouse_y))
			{
				deal_with_clicked_object(ed, &sector->objects->items[j]);
				return (e_true);
			}
		}
	}
	return (e_false);
}

enum e_bool	click_on_enemy(t_editor *ed, t_map *map, int mouse_x, int mouse_y)
{
	int					i;
	t_linked_enemies	*enemies;
	t_sector			*sector;
	t_rect				rect;

	i = -1;
	while (++i < map->sectors->count)
	{
		sector = map->sectors->items[i];
		enemies = sector->enemies;
		while (enemies)
		{
			rect = create_rect(ed->map_offset.x + enemies->item.object->x
					* ed->zoom - 6, ed->map_offset.y - enemies->item.object->y
					* ed->zoom - 6, 12, 12);
			if (is_in_rect(&rect, mouse_x, mouse_y))
			{
				deal_with_clicked_enemy(ed, &enemies->item);
				return (e_true);
			}
			enemies = enemies->next;
		}
	}
	return (e_false);
}

enum e_bool	click_on_pickable(t_editor *ed, t_map *map, int mouse_x,
				int mouse_y)
{
	int			i;
	t_pickables	*pickables;
	t_sector	*sector;
	t_rect		rect;

	i = -1;
	while (++i < map->sectors->count)
	{
		sector = map->sectors->items[i];
		pickables = sector->pickables;
		while (pickables)
		{
			rect = create_rect(ed->map_offset.x + pickables->item.object->x
					* ed->zoom - 6, ed->map_offset.y - pickables->item.object->y
					* ed->zoom - 6, 12, 12);
			if (is_in_rect(&rect, mouse_x, mouse_y))
			{
				deal_with_clicked_pickable(ed, &pickables->item);
				return (e_true);
			}
			pickables = pickables->next;
		}
	}
	return (e_false);
}
