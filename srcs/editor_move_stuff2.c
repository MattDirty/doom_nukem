/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_move_stuff2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfatton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/20 07:34:07 by lfatton           #+#    #+#             */
/*   Updated: 2019/04/20 07:34:10 by lfatton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "editor_walls_nodes.h"
#include "in_which_sector.h"
#include "editor_checks.h"

void	move_map(t_editor *ed, SDL_Scancode key)
{
	if (key == SDL_SCANCODE_UP)
		ed->map_offset.y += 0.5 * ed->zoom;
	if (key == SDL_SCANCODE_DOWN)
		ed->map_offset.y -= 0.5 * ed->zoom;
	if (key == SDL_SCANCODE_LEFT)
		ed->map_offset.x += 0.5 * ed->zoom;
	if (key == SDL_SCANCODE_RIGHT)
		ed->map_offset.x -= 0.5 * ed->zoom;
}

void	move_walls_nodes(t_editor *ed, double x, double y)
{
	t_wall_nodes	*nodes;
	t_coords		delta;

	nodes = ed->dragged.nodes;
	delta.x = (x - ed->map_offset.x) / ed->zoom - *nodes->item.x;
	delta.y = (ed->map_offset.y - y) / ed->zoom - *nodes->item.y;
	while (nodes)
	{
		*nodes->item.x += delta.x;
		*nodes->item.y += delta.y;
		nodes = nodes->next;
	}
	nodes = ed->dragged.nodes;
	if (!is_map_valid(ed->linked_walls, ed->map))
	{
		while (nodes)
		{
			*nodes->item.x -= delta.x;
			*nodes->item.y -= delta.y;
			nodes = nodes->next;
		}
		Mix_PlayChannel(-1, ed->sounds->meeeh, 0);
		return ;
	}
	ed->map_is_updated = e_false;
}

void	move_player_spawn(t_editor *ed, double x, double y)
{
	t_sector	*sector;
	double		new_x;
	double		new_y;

	new_x = (x - ed->map_offset.x) / ed->zoom;
	new_y = (ed->map_offset.y - y) / ed->zoom;
	if (!(sector = in_which_sector((t_coords){new_x, new_y}, ed->map->sectors)))
	{
		Mix_PlayChannel(-1, ed->sounds->meeeh, 0);
		return ;
	}
	ed->map->spawn.x = new_x;
	ed->map->spawn.y = new_y;
	ed->map_is_updated = e_false;
}
