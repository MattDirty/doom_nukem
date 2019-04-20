/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_walls_nodes.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfatton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/20 06:28:19 by lfatton           #+#    #+#             */
/*   Updated: 2019/04/20 06:28:21 by lfatton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor_walls_nodes.h"
#include "walls.h"
#include "doom.h"

void	free_walls_nodes(t_wall_nodes *nodes)
{
	t_wall_nodes	*next;

	while (nodes)
	{
		next = nodes->next;
		free(nodes);
		nodes = next;
	}
}

void	add_wall_node_to_list(t_wall_nodes **list, t_wall *wall, t_coords point)
{
	t_wall_nodes	*ptr;
	t_wall_nodes	*new;

	if (!(new = (t_wall_nodes *)malloc(sizeof(t_wall_nodes))))
		error_doom("Couldn't malloc wall_nodes");
	new->next = NULL;
	new->item.wall = wall;
	if (fabs(wall->segment.x1 - point.x) < 0.01 && fabs(wall->segment.y1
			- point.y) < 0.01)
	{
		new->item.x = &wall->segment.x1;
		new->item.y = &wall->segment.y1;
	}
	else
	{
		new->item.x = &wall->segment.x2;
		new->item.y = &wall->segment.y2;
	}
	if (!(*list))
	{
		*list = new;
		return ;
	}
	ptr = *list;
	while (ptr->next)
		ptr = ptr->next;
	ptr->next = new;
}
