/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_move_stuff.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfatton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/20 07:34:52 by lfatton           #+#    #+#             */
/*   Updated: 2019/04/20 07:34:54 by lfatton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "editor_walls_nodes.h"
#include "in_which_sector.h"

void	move_enemy(t_editor *ed, double x, double y)
{
	t_sector			*sector;
	t_sector			*old_sector;
	t_coords			new;
	t_linked_enemies	*extracted_node;

	old_sector = find_enemy_sector(ed->map->sectors, ed->dragged.enemy);
	new.x = (x - ed->map_offset.x) / ed->zoom;
	new.y = (ed->map_offset.y - y) / ed->zoom;
	if (!(sector = in_which_sector(new, ed->map->sectors)))
	{
		Mix_PlayChannel(-1, ed->sounds->meeeh, 0);
		return ;
	}
	if (old_sector != sector)
	{
		extracted_node = extract_enemy(&old_sector->enemies, ed->dragged.enemy);
		add_enemy(&sector->enemies, extracted_node);
	}
	ed->dragged.enemy->object->x = new.x;
	ed->dragged.enemy->object->y = new.y;
	ed->map_is_updated = e_false;
}

void	move_pickable(t_editor *ed, double x, double y)
{
	t_sector	*sector;
	double		new_x;
	double		new_y;

	sector = find_pickable_sector(ed->map->sectors, ed->dragged.pickable);
	new_x = (x - ed->map_offset.x) / ed->zoom;
	new_y = (ed->map_offset.y - y) / ed->zoom;
	if (!is_in_sector((t_coords){new_x, new_y}, sector))
	{
		Mix_PlayChannel(-1, ed->sounds->meeeh, 0);
		return ;
	}
	ed->dragged.pickable->object->x = new_x;
	ed->dragged.pickable->object->y = new_y;
	ed->map_is_updated = e_false;
}

void	move_object(t_editor *ed, double x, double y)
{
	t_sector	*sector;
	double		new_x;
	double		new_y;

	sector = find_object_sector(ed->map->sectors, ed->dragged.object);
	new_x = (x - ed->map_offset.x) / ed->zoom;
	new_y = (ed->map_offset.y - y) / ed->zoom;
	if (!is_in_sector((t_coords){new_x, new_y}, sector))
	{
		Mix_PlayChannel(-1, ed->sounds->meeeh, 0);
		return ;
	}
	ed->dragged.object->x = new_x;
	ed->dragged.object->y = new_y;
	ed->map_is_updated = e_false;
}
