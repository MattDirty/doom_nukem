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

void		free_walls_nodes(t_wall_nodes *nodes)
{
	t_wall_nodes	*next;

	while (nodes)
	{
		next = nodes->next;
		free(nodes);
		nodes = next;
	}
}

static void	add_to_last(t_wall_nodes **list, t_wall_nodes *new)
{
	t_wall_nodes *ptr;

	ptr = *list;
	while (ptr->next)
		ptr = ptr->next;
	ptr->next = new;
}

void		add_wall_node_to_list(t_wall_nodes **list, t_wall *w, t_coords p)
{
	t_wall_nodes	*new;

	if (!(new = (t_wall_nodes *)malloc(sizeof(t_wall_nodes))))
		error_doom("Couldn't malloc wall_nodes");
	new->next = NULL;
	new->item.wall = w;
	if (fabs(w->segment.x1 - p.x) < 0.01 && fabs(w->segment.y1 - p.y) < 0.01)
	{
		new->item.x = &w->segment.x1;
		new->item.y = &w->segment.y1;
	}
	else
	{
		new->item.x = &w->segment.x2;
		new->item.y = &w->segment.y2;
	}
	if (!(*list))
	{
		*list = new;
		return ;
	}
	add_to_last(list, new);
}
