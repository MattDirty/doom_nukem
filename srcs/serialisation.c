/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serialisation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtorsell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/20 03:37:21 by mtorsell          #+#    #+#             */
/*   Updated: 2019/04/20 03:37:25 by mtorsell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdlib.h>
#include <sys/stat.h>
#include "libft.h"
#include "doom.h"
#include "serialisation.h"

void	check_if_file_is_valid(int *fd, char *filename)
{
	struct stat st;
	struct stat st_verif;

	if ((stat(filename, &st)) < 0)
		error_doom("File doesn't seem to exist, are you sure you have the ri"
			"ght path ?");
	if (st.st_size > 100000000)
		error_doom("This map is too big ! You ain't fooling anyone, "
			"you dirty creep.");
	if (st.st_size < 1000000)
		error_doom("Come on, that's way too small for a map file ! Try doing ./"
			"editor real_map_name and stop trying to break stuff ...");
	*fd = open(filename, O_RDONLY);
	if (*fd <= 0)
		error_doom("Couldn't open file");
	read(*fd, &st_verif.st_size, sizeof(st_verif.st_size));
	if (st_verif.st_size != st.st_size)
		error_doom("It seems your map has been corrupted. That's naughty!");
}

void	read_file(char *filename, t_env *e)
{
	int fd;

	check_if_file_is_valid(&fd, filename);
	read_fonts_from_file(fd, &e->fonts);
	read_sounds_from_file(fd, &e->sounds);
	read_textures_from_file(fd, &e->textures);
	read_map_from_file(fd, e->textures, &e->map);
	close(fd);
}

void	read_file_editor(char *filename, t_read_data *e)
{
	int fd;

	check_if_file_is_valid(&fd, filename);
	read_fonts_from_file(fd, e->fonts);
	read_sounds_from_file(fd, e->sounds);
	read_textures_from_file(fd, e->textures);
	read_map_from_file(fd, *e->textures, e->map);
	close(fd);
}

void	write_file_protections(int fd, char *filename)
{
	struct stat st;

	if ((stat(filename, &st)) < 0)
		error_doom("Wow, that really shouldn't happen. It seems the map doesn't"
			"exist ...");
	write(fd, &st.st_size, sizeof(st.st_size));
}

void	write_file(char *filename, t_textures *textures, t_map *map)
{
	int fd;

	fd = open(filename, O_WRONLY | O_CREAT, S_IRWXU | S_IRWXG | S_IRWXO);
	if (fd <= 0)
		error_doom("couldn't open file");
	write_file_protections(fd, filename);
	write_fonts_to_file(fd);
	write_sounds_to_file(fd);
	write_textures_to_file(fd, textures);
	write_map_to_file(fd, map);
	close(fd);
	if ((fd = open(filename, O_WRONLY)) <= 0)
		error_doom("There was a problem while reopening the file.");
	write_file_protections(fd, filename);
	close(fd);
}
