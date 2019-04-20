/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_add_elements_in_map.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfatton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/20 05:49:53 by lfatton           #+#    #+#             */
/*   Updated: 2019/04/20 05:49:56 by lfatton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor_mouse_clicks.h"
#include "editor_walls_nodes.h"
#include "in_which_sector.h"
#include "editor_panel_buttons.h"
#include "editor_checks.h"

void	try_sector_creation(t_editor *ed, int mouse_x, int mouse_y)
{
	t_wall		*wall;
	t_sector	*new_sector;
	t_sector	*linked_sector;

	ed->state = e_null;
	ed->pos.x = (double)(mouse_x - ed->map_offset.x) / ed->zoom;
	ed->pos.y = (double)(ed->map_offset.y - mouse_y) / ed->zoom;
	if (new_node_pos_valid(ed, ed->pos))
		return ;
	new_sector = create_new_sector(ed->map->sectors);
	linked_sector = find_wall_sector(ed->map->sectors, ed->selected.wall);
	copy_sector_floor_ceil(new_sector, linked_sector);
	wall = create_wall_copy(ed->selected.wall);
	wall->segment.x1 = ed->pos.x;
	wall->segment.y1 = ed->pos.y;
	add_wall_to_sector(new_sector, wall);
	wall = create_wall_copy(ed->selected.wall);
	wall->segment.x2 = ed->pos.x;
	wall->segment.y2 = ed->pos.y;
	add_wall_to_sector(new_sector, wall);
	transform_wall_to_portal(ed->selected.wall, linked_sector, new_sector);
	add_wall_to_sector(new_sector, ed->selected.wall);
	free_linked_walls_nodes(ed->linked_walls);
	create_linked_walls_from_sectors(ed->map->sectors, &ed->linked_walls,
			&ed->linked_walls_count);
}

void	try_lever_creation(t_editor *ed, int mouse_x, int mouse_y)
{
	t_wall		*wall;
	t_wall		*door;

	ed->state = e_null;
	ed->pos.x = (double)(mouse_x - ed->map_offset.x) / ed->zoom;
	ed->pos.y = (double)(ed->map_offset.y - mouse_y) / ed->zoom;
	door = ed->selected.wall;
	if (!click_on_walls(ed, ed->linked_walls, mouse_x, mouse_y))
	{
		Mix_PlayChannel(-1, ed->sounds->meeeh, 0);
		return ;
	}
	wall = ed->selected.wall;
	if (wall->type != e_wall || wall->lever != NULL)
	{
		Mix_PlayChannel(-1, ed->sounds->meeeh, 0);
		return ;
	}
	create_lever(wall, door, ed->textures);
	ed->map_is_updated = e_false;
}

void	create_object_in_sector(t_editor *ed, int mouse_x, int mouse_y)
{
	t_sector	*sector;

	ed->pos.x = (double)(mouse_x - ed->map_offset.x) / ed->zoom;
	ed->pos.y = (double)(ed->map_offset.y - mouse_y) / ed->zoom;
	sector = in_which_sector(ed->pos, ed->map->sectors);
	if (sector)
		ed->selected.object = add_new_object_to_sector_at_pos(
				sector, ed->pos, ed->textures);
	if (!ed->selected.object)
		Mix_PlayChannel(-1, ed->sounds->meeeh, 0);
	ed->state = e_null;
	ed->map_is_updated = e_false;
}

void	create_enemy_in_sector(t_editor *ed, int mouse_x, int mouse_y)
{
	t_sector			*sector;
	t_linked_enemies	*enemy;

	ed->pos.x = (double)(mouse_x - ed->map_offset.x) / ed->zoom;
	ed->pos.y = (double)(ed->map_offset.y - mouse_y) / ed->zoom;
	sector = in_which_sector(ed->pos, ed->map->sectors);
	if (sector)
	{
		enemy = add_new_enemy_to_sector_at_pos(sector, ed->pos, ed->textures);
		if (!enemy)
			ed->selected.enemy = NULL;
		else
			ed->selected.enemy = &enemy->item;
	}
	if (!ed->selected.enemy)
		Mix_PlayChannel(-1, ed->sounds->meeeh, 0);
	ed->state = e_null;
	ed->map_is_updated = e_false;
}

void	create_pickable_in_sector(t_editor *ed, int mouse_x, int mouse_y)
{
	t_sector	*sector;
	t_pickables	*pickables;

	ed->pos.x = (double)(mouse_x - ed->map_offset.x) / ed->zoom;
	ed->pos.y = (double)(ed->map_offset.y - mouse_y) / ed->zoom;
	sector = in_which_sector(ed->pos, ed->map->sectors);
	if (sector)
	{
		pickables = add_new_pickable_to_sector_at_pos(sector, ed->pos,
				ed->textures);
		if (!pickables)
			ed->selected.pickable = NULL;
		else
			ed->selected.pickable = &pickables->item;
	}
	if (!ed->selected.pickable)
		Mix_PlayChannel(-1, ed->sounds->meeeh, 0);
	ed->state = e_null;
	ed->map_is_updated = e_false;
}
