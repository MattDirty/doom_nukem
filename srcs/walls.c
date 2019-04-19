/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtorsell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/20 01:25:33 by mtorsell          #+#    #+#             */
/*   Updated: 2019/04/20 01:25:38 by mtorsell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "walls.h"
#include "textures.h"
#include "doom.h"

t_wall		*create_wall_copy(t_wall *wall)
{
	t_wall *new_wall;

	if (!(new_wall = (t_wall *)malloc(sizeof(t_wall))))
		error_doom("Couldn't allocate copy of wall");
	*new_wall = *wall;
	new_wall->wall_object = NULL;
	new_wall->lever = NULL;
	return (new_wall);
}

int			wall_index(t_linked_walls *linked_walls, t_wall *wall)
{
	int i;

	i = 0;
	while (linked_walls)
	{
		if (wall == linked_walls->wall)
			return (i);
		linked_walls = linked_walls->next;
		i++;
	}
	return (-1);
}

t_wall		*wall_at_index(t_linked_walls *linked_walls, int index)
{
	int i;

	i = 0;
	while (linked_walls->next)
	{
		if (index == i)
			return (linked_walls->wall);
		linked_walls = linked_walls->next;
		i++;
	}
	return (NULL);
}

void		free_linked_walls_nodes(t_linked_walls *linked_walls)
{
	if (!linked_walls)
		return ;
	free_linked_walls_nodes(linked_walls->next);
	free(linked_walls);
}

void		free_linked_walls(t_linked_walls *linked_walls)
{
	if (!linked_walls)
		return ;
	free_linked_walls(linked_walls->next);
	if (linked_walls->wall)
	{
		if (linked_walls->wall->wall_object)
			free(linked_walls->wall->wall_object);
		if (linked_walls->wall->lever)
		{
			if (linked_walls->wall->lever->wall_object)
				free(linked_walls->wall->lever->wall_object);
			free(linked_walls->wall->lever);
		}
		free(linked_walls->wall);
	}
	free(linked_walls);
}
