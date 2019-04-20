/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sectors.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtorsell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/20 03:51:07 by mtorsell          #+#    #+#             */
/*   Updated: 2019/04/20 03:51:10 by mtorsell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "textures.h"
#include "serialisation.h"
#include "sectors.h"
#include "objects.h"
#include "doom.h"
#include "enemies.h"
#include "utils.h"

void	free_sectors(t_sectors *sectors)
{
	int				i;
	t_sector		*sector;
	t_linked_walls	*linked_walls;
	int				count;

	create_linked_walls_from_sectors(sectors, &linked_walls, &count);
	free_linked_walls(linked_walls);
	i = 0;
	while (i < sectors->count)
	{
		sector = sectors->items[i];
		free(sector->walls->items);
		free(sector->walls);
		free_objects(sector->objects);
		free_enemies(sector->enemies);
		free_pickables(sector->pickables);
		free(sector);
		i++;
	}
	free(sectors->items);
	free(sectors);
}

void	read_sectors_from_file2(t_i_coords norme, t_sectors **sectors,
			t_textures *textures, t_linked_walls *linked_walls)
{
	t_sector	*sector;
	int			i;

	i = 0;
	while (i < norme.x)
	{
		sector = (*sectors)->items[i];
		find_texture_from_file(norme.y, textures, &sector->floor);
		find_texture_from_file(norme.y, textures, &sector->ceil);
		read_walls_from_file(norme.y, linked_walls, &sector->walls);
		if (read(norme.y, &sector->open_sky, sizeof(sector->open_sky)) <= 0)
			error_doom("couldn't read sector open_sky");
		if (read(norme.y, &sector->light, sizeof(sector->light)) <= 0)
			error_doom("couldn't read sector light");
		read_objects_from_file(norme.y, textures, &sector->objects);
		read_enemies_from_file(norme.y, textures, &sector->enemies);
		read_pickables_from_file(norme.y, textures, &sector->pickables);
		i++;
	}
}

void	read_sectors_from_file(
			int fd,
			t_textures *textures,
			t_sectors **sectors)
{
	int				count;
	int				i;
	t_sector		*sector;
	t_linked_walls	*linked_walls;

	if (!(*sectors = (t_sectors *)malloc(sizeof(t_sectors))))
		error_doom("couldn't malloc t_sectors");
	if (read(fd, &count, sizeof(count)) <= 0)
		error_doom("couldn't read sectors count");
	(*sectors)->count = count;
	if (!((*sectors)->items = (t_sector **)malloc(sizeof(t_sector *) * count)))
		error_doom("this malloc hasn't been protected since april eighteenth");
	i = 0;
	while (i < count)
	{
		if (!(sector = (t_sector *)malloc(sizeof(t_sector))))
			error_doom("yet another error");
		(*sectors)->items[i] = sector;
		i++;
	}
	read_linked_walls_from_file(fd, *sectors, textures, &linked_walls);
	read_sectors_from_file2((t_i_coords){count, fd},
		sectors, textures, linked_walls);
	free_linked_walls_nodes(linked_walls);
}

void	write_sectors_to_file(int fd, t_sectors *sectors)
{
	int				i;
	t_sector		*sector;
	t_linked_walls	*linked_walls;

	if (write(fd, &sectors->count, sizeof(sectors->count)) <= 0)
		error_doom("couldn't write sectors count");
	write_linked_walls_to_file(fd, sectors, &linked_walls);
	i = 0;
	while (i < sectors->count)
	{
		sector = sectors->items[i];
		write_str_to_file(fd, sector->floor->userdata);
		write_str_to_file(fd, sector->ceil->userdata);
		write_walls_to_file(fd, linked_walls, sector->walls);
		if (write(fd, &sector->open_sky, sizeof(sector->open_sky)) <= 0)
			error_doom("couldn't write sector open_sky");
		if (write(fd, &sector->light, sizeof(sector->light)) <= 0)
			error_doom("couldn't write sector light");
		write_objects_to_file(fd, sector->objects);
		write_enemies_to_file(fd, sector->enemies);
		write_pickables_to_file(fd, sector->pickables);
		i++;
	}
	free_linked_walls_nodes(linked_walls);
}

int		sector_index(t_sectors *sectors, t_sector *sector)
{
	int i;

	i = 0;
	while (i < sectors->count)
	{
		if (sector == sectors->items[i])
			return (i);
		i++;
	}
	return (-1);
}
