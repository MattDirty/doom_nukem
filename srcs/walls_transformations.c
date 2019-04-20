/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls_transformations.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtorsell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/20 00:47:00 by mtorsell          #+#    #+#             */
/*   Updated: 2019/04/20 00:47:04 by mtorsell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "walls.h"

void		transform_door_to_portal(t_wall *wall, t_linked_walls *node)
{
	while (node->next)
	{
		if (node->wall->lever && node->wall->lever->door == wall)
		{
			free(node->wall->lever->wall_object);
			node->wall->lever->wall_object = NULL;
			free(node->wall->lever);
			node->wall->lever = NULL;
		}
		node = node->next;
	}
	wall->texture = NULL;
	wall->type = e_portal;
	wall->to_infinity = e_false;
}

void		transform_portal_to_door(t_wall *wall, SDL_Surface *texture)
{
	wall->type = e_transparent_wall;
	wall->to_infinity = e_false;
	wall->texture = texture;
}

void		transform_window_to_wall(t_wall *wall)
{
	wall->type = e_wall;
	wall->links.sector1 = NULL;
	wall->links.sector2 = NULL;
}

void		transform_wall_to_window(t_wall *wall, t_sector *sector)
{
	wall->type = e_transparent_wall;
	wall->links.sector1 = sector;
	wall->links.sector2 = sector;
	wall->to_infinity = e_true;
}

void		transform_wall_to_portal(t_wall *wall, t_sector *s1, t_sector *s2)
{
	wall->type = e_portal;
	wall->to_infinity = e_false;
	wall->texture = NULL;
	wall->links.sector1 = s1;
	wall->links.sector2 = s2;
}
