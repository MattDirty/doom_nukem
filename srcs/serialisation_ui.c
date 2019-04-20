/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serialisation_ui.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfatton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 14:20:25 by lfatton           #+#    #+#             */
/*   Updated: 2019/04/19 14:20:28 by lfatton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "utils.h"
#include "doom.h"
#include "serialisation.h"

void	read_spawn_from_file(int fd, t_coords *spawn, int *index)
{
	if (read(fd, &(spawn->x), sizeof(spawn->x)) <= 0)
		error_doom("couldn't read player spawn coords");
	if (read(fd, &(spawn->y), sizeof(spawn->y)) <= 0)
		error_doom("couldn't read player spawn coords");
	if (read(fd, index, sizeof(*index)) <= 0)
		error_doom("Couldn't read player spawn index");
}

void	write_spawn_to_file(int fd, t_coords spawn, int index)
{
	if (write(fd, &(spawn.x), sizeof(spawn.x)) <= 0)
		error_doom("couldn't write player spawn coords");
	if (write(fd, &(spawn.y), sizeof(spawn.y)) <= 0)
		error_doom("couldn't write player spawn coords");
	if (write(fd, &(index), sizeof(index)) <= 0)
		error_doom("Couldn't write player spawn index");
}

void	read_hud_from_file(int fd, t_textures *textures, t_hud *hud)
{
	find_texture_from_file(fd, textures, &hud->sun);
	find_texture_from_file(fd, textures, &hud->moon);
	find_texture_from_file(fd, textures, &hud->cross[0]);
	find_texture_from_file(fd, textures, &hud->cross[1]);
	find_texture_from_file(fd, textures, &hud->cross[2]);
	find_texture_from_file(fd, textures, &hud->bullet);
	find_texture_from_file(fd, textures, &hud->happy_face);
	find_texture_from_file(fd, textures, &hud->meh_face);
	find_texture_from_file(fd, textures, &hud->sad_face);
	find_texture_from_file(fd, textures, &hud->dead_face);
	find_texture_from_file(fd, textures, &hud->badass_face);
	find_texture_from_file(fd, textures, &hud->sehr_happy_face);
	find_texture_from_file(fd, textures, &hud->hurt_face);
}

void	write_hud_to_file(int fd, t_hud hud)
{
	write_str_to_file(fd, hud.sun->userdata);
	write_str_to_file(fd, hud.moon->userdata);
	write_str_to_file(fd, hud.cross[0]->userdata);
	write_str_to_file(fd, hud.cross[1]->userdata);
	write_str_to_file(fd, hud.cross[2]->userdata);
	write_str_to_file(fd, hud.bullet->userdata);
	write_str_to_file(fd, hud.happy_face->userdata);
	write_str_to_file(fd, hud.meh_face->userdata);
	write_str_to_file(fd, hud.sad_face->userdata);
	write_str_to_file(fd, hud.dead_face->userdata);
	write_str_to_file(fd, hud.badass_face->userdata);
	write_str_to_file(fd, hud.sehr_happy_face->userdata);
	write_str_to_file(fd, hud.hurt_face->userdata);
}
