/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfatton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 14:02:45 by lfatton           #+#    #+#             */
/*   Updated: 2019/04/19 14:02:47 by lfatton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "map.h"
#include "textures.h"
#include "serialisation.h"
#include "doom.h"
#include "ui.h"

void	free_map(t_map *map)
{
	free_sectors(map->sectors);
	free(map);
}

void	read_map_from_file(int fd, t_textures *textures, t_map **map)
{
	if (!(*map = (t_map *)malloc(sizeof(t_map))))
		error_doom("couldn't malloc t_map");
	(*map)->daytime = 0;
	read_sectors_from_file(fd, textures, &(*map)->sectors);
	read_spawn_from_file(fd, &(*map)->spawn, &(*map)->player_spawn_index);
	read_hud_from_file(fd, textures, &(*map)->hud);
	find_texture_from_file(fd, textures, &(*map)->daysky);
	find_texture_from_file(fd, textures, &(*map)->nightsky);
	find_texture_from_file(fd, textures, &(*map)->melee_sprite);
	find_texture_from_file(fd, textures, &(*map)->gun_sprites[0]);
	find_texture_from_file(fd, textures, &(*map)->gun_sprites[1]);
	find_texture_from_file(fd, textures, &(*map)->gun_sprites[2]);
	find_texture_from_file(fd, textures, &(*map)->gun_sprites[3]);
	find_texture_from_file(fd, textures, &(*map)->gun_sprites[4]);
	find_texture_from_file(fd, textures, &(*map)->shotgun_sprites[0]);
	find_texture_from_file(fd, textures, &(*map)->shotgun_sprites[1]);
	find_texture_from_file(fd, textures, &(*map)->shotgun_sprites[2]);
	find_texture_from_file(fd, textures, &(*map)->vacuum_sprite);
}

void	write_map_to_file(int fd, t_map *map)
{
	int i;

	i = -1;
	write_sectors_to_file(fd, map->sectors);
	write_spawn_to_file(fd, map->spawn, map->player_spawn_index);
	write_hud_to_file(fd, map->hud);
	write_str_to_file(fd, map->daysky->userdata);
	write_str_to_file(fd, map->nightsky->userdata);
	write_str_to_file(fd, map->melee_sprite->userdata);
	write_str_to_file(fd, map->gun_sprites[0]->userdata);
	write_str_to_file(fd, map->gun_sprites[1]->userdata);
	write_str_to_file(fd, map->gun_sprites[2]->userdata);
	write_str_to_file(fd, map->gun_sprites[3]->userdata);
	write_str_to_file(fd, map->gun_sprites[4]->userdata);
	write_str_to_file(fd, map->shotgun_sprites[0]->userdata);
	write_str_to_file(fd, map->shotgun_sprites[1]->userdata);
	write_str_to_file(fd, map->shotgun_sprites[2]->userdata);
	write_str_to_file(fd, map->vacuum_sprite->userdata);
}
