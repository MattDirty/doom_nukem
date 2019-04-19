/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls_rw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtorsell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/20 01:09:49 by mtorsell          #+#    #+#             */
/*   Updated: 2019/04/20 01:09:54 by mtorsell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "doom.h"
#include "walls.h"
#include "serialisation.h"

static void		fix_levers(t_linked_walls *linked_walls)
{
	t_linked_walls	*node;
	t_wall			*door;

	node = linked_walls;
	while (node->wall)
	{
		if (node->wall->lever)
		{
			door = wall_at_index(linked_walls, node->wall->lever->door_index);
			if (door == NULL)
				error_doom("couldn't find door");
			node->wall->lever->door = door;
		}
		node = node->next;
	}
}

static int		add_wall_to_serialiser(t_linked_walls *linked_walls,
					t_wall *wall)
{
	int		i;

	i = 0;
	while (linked_walls->wall)
	{
		if (linked_walls->wall == wall)
			return (i);
		linked_walls = linked_walls->next;
		i++;
	}
	linked_walls->wall = wall;
	if (!(linked_walls->next = (t_linked_walls*)malloc(sizeof(t_linked_walls))))
		error_doom("couldn't malloc t_linked_walls");
	linked_walls->next->next = NULL;
	linked_walls->next->wall = NULL;
	return (i);
}

void			create_linked_walls_from_sectors(t_sectors *sectors,
		t_linked_walls **linked_walls,
		int *count)
{
	int		i;
	int		j;
	int		index;

	if (!(*linked_walls = (t_linked_walls*)malloc(sizeof(t_linked_walls))))
		error_doom("couldn't malloc linked walls");
	(*linked_walls)->next = NULL;
	(*linked_walls)->wall = NULL;
	*count = 0;
	i = 0;
	while (i < sectors->count)
	{
		j = 0;
		while (j < sectors->items[i]->walls->count)
		{
			index = add_wall_to_serialiser(*linked_walls,
					sectors->items[i]->walls->items[j]);
			if (index >= *count)
				*count = index + 1;
			j++;
		}
		i++;
	}
}

void			read_linked_walls_from_file(
		int fd,
		t_sectors *sectors,
		t_textures *textures,
		t_linked_walls **linked_walls)
{
	int		i;
	int		count;
	t_wall	*wall;

	if (!(*linked_walls = (t_linked_walls*)malloc(sizeof(t_linked_walls))))
		error_doom("couldn't malloc t_linked_walls");
	(*linked_walls)->next = NULL;
	(*linked_walls)->wall = NULL;
	if (read(fd, &count, sizeof(count)) <= 0)
		error_doom("couldn't read linked_walls");
	i = 0;
	while (i < count)
	{
		read_wall_from_file(fd, sectors, textures, &wall);
		add_wall_to_serialiser(*linked_walls, wall);
		i++;
	}
	fix_levers(*linked_walls);
}

void			write_linked_walls_to_file(int fd, t_sectors *sectors,
		t_linked_walls **p_linked_walls)
{
	t_linked_walls	*linked_walls;
	int				count;

	create_linked_walls_from_sectors(sectors, p_linked_walls, &count);
	linked_walls = *p_linked_walls;
	if (write(fd, &count, sizeof(count)) <= 0)
		error_doom("couldn't write walls count");
	while (linked_walls->wall)
	{
		write_wall_to_file(fd, sectors, *p_linked_walls, linked_walls->wall);
		linked_walls = linked_walls->next;
	}
}
