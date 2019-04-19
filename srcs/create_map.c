/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badhont <badhont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 19:36:17 by badhont           #+#    #+#             */
/*   Updated: 2019/04/18 10:12:35 by badhont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

t_map		*create_map(t_textures *textures)
{
	int			i;
	int			j;
	t_walls*	walls;
	t_map		*map;

	if (!(map = (t_map*)malloc(sizeof(t_map))))
		error_doom("error: cannot allocate memory for struct map");

	if (!(map->sectors = (t_sectors*)malloc(sizeof(t_sectors))))
		error_doom("t_sectors");

	map->sectors->count = 2;
	if (!(map->sectors->items =
				(t_sector**)malloc(map->sectors->count * sizeof(t_sector*))))
		error_doom("Can't allocate sectors");

	i = 0;
	while (i < map->sectors->count)
	{
        if (!(map->sectors->items[i] = (t_sector*)malloc(sizeof(t_sector))))
            error_doom("BUS ERROR !!!11");
        i++;
    }
	i = 0;
	while (i < map->sectors->count)
	{
		if (!(map->sectors->items[i]->walls = (t_walls*)malloc(sizeof(t_walls))))
			error_doom("t_walls");

        find_texture_by_name(textures, "textures/flats/grass.bmp", &map->sectors->items[i]->floor);
        find_texture_by_name(textures, "textures/flats/dirt.bmp", &map->sectors->items[i]->ceil);
        map->sectors->items[i]->open_sky = e_false;
        map->sectors->items[i]->objects = (t_objects*)malloc(sizeof(t_objects));
        map->sectors->items[i]->objects->items = NULL;
            map->sectors->items[i]->objects->count = 0;
            map->sectors->items[i]->objects->items = (t_object*)malloc(
                    sizeof(t_object) * map->sectors->items[i]->objects->count);

		walls = map->sectors->items[i]->walls;
		find_texture_by_name(
				textures,
				"textures/walls/stones.bmp",
				&map->sectors->items[1]->floor);
		find_texture_by_name(
				textures,
				"textures/flats/dirt.bmp",
				&map->sectors->items[2]->floor);
		walls->count = 4;

		if (!(walls->items = (t_wall**)malloc(walls->count * sizeof(t_wall*))))
			error_doom("Can't allocate walls");

        j = 0;
        while (j < walls->count)
            if (!(walls->items[j++] = (t_wall*)malloc(sizeof(t_wall))))
                error_doom("Can't allocate wall");

		walls->items[0]->segment = create_segment(0, 0 + i * 4, 0, 4 + i * 4);
		walls->items[1]->segment = create_segment(0, 4 + i * 4, 4, 4 + i * 4);
		walls->items[2]->segment = create_segment(4, 4 + i * 4, 4, 0 + i * 4);
		walls->items[3]->segment = create_segment(4, 0 + i * 4, 0, 0 + i * 4);

		j = 0;
		while (j < walls->count)
		{
            walls->items[j]->wall_object = NULL;
            walls->items[j]->lever = NULL;
		    walls->items[j]->type = e_wall;
		    walls->items[j]->to_infinity = e_false;
            walls->items[j]->wall_offset = 0;
			j++;
		}
		i++;
	}
    find_texture_by_name(textures, "textures/skybox/day.bmp", &map->daysky);
    find_texture_by_name(textures, "textures/skybox/night.bmp", &map->nightsky);
    find_texture_by_name(textures, "textures/hud/sun.bmp", &map->hud.sun);
    find_texture_by_name(textures, "textures/hud/moon.bmp", &map->hud.moon);
	find_texture_by_name(textures, "textures/hud/health/ico1.bmp", &map->hud.cross[0]);
	find_texture_by_name(textures, "textures/hud/health/ico2.bmp", &map->hud.cross[1]);
	find_texture_by_name(textures, "textures/hud/health/ico3.bmp", &map->hud.cross[2]);
	find_texture_by_name(textures, "textures/hud/bullet.bmp", &map->hud.bullet);
	find_texture_by_name(textures, "textures/hud/faces/happy.bmp", &map->hud.happy_face);
	find_texture_by_name(textures, "textures/hud/faces/meh.bmp", &map->hud.meh_face);
	find_texture_by_name(textures, "textures/hud/faces/sad.bmp", &map->hud.sad_face);
	find_texture_by_name(textures, "textures/hud/faces/dead.bmp", &map->hud.dead_face);
	find_texture_by_name(textures, "textures/hud/faces/badass.bmp", &map->hud.badass_face);
	find_texture_by_name(textures, "textures/hud/faces/sehr_happy.bmp", &map->hud.sehr_happy_face);
	find_texture_by_name(textures, "textures/hud/faces/hurt.bmp", &map->hud.hurt_face);
    find_texture_by_name(textures, "textures/weapons/dwa.bmp", &map->melee_sprite);
    find_texture_by_name(textures, "textures/weapons/gun_1.bmp", &map->gun_sprites[0]);
    find_texture_by_name(textures, "textures/weapons/gun_2.bmp", &map->gun_sprites[1]);
    find_texture_by_name(textures, "textures/weapons/gun_3.bmp", &map->gun_sprites[2]);
    find_texture_by_name(textures, "textures/weapons/gun_firing.bmp", &map->gun_sprites[3]);
    find_texture_by_name(textures, "textures/weapons/gun_cooldown.bmp", &map->gun_sprites[4]);
    find_texture_by_name(textures, "textures/weapons/shotgun_1.bmp", &map->shotgun_sprites[0]);
    find_texture_by_name(textures, "textures/weapons/shotgun_cooldown.bmp", &map->shotgun_sprites[1]);
    find_texture_by_name(textures, "textures/weapons/shotgun_firing.bmp", &map->shotgun_sprites[2]);
    find_texture_by_name(textures, "textures/weapons/blackhole_destroyer.bmp", &map->vacuum_sprite);
    map->daytime = e_true;
    map->spawn.x = 1;
    map->spawn.y = 1;

	return (map);
}

t_textures	*load_textures(void)
{
    t_textures	*textures;

    if (!(textures = (t_textures*)malloc(sizeof(t_textures))))
        error_doom("could not allocate textures");
    textures->first = NULL;
    add_bitmap_file_to_textures(textures, "textures/walls/stones.bmp");
    add_bitmap_file_to_textures(textures, "textures/walls/brickwall2.bmp");
    add_bitmap_file_to_textures(textures, "textures/walls/fence.bmp");
    add_bitmap_file_to_textures(textures, "textures/walls/window.bmp");
    add_bitmap_file_to_textures(textures, "textures/flats/grass.bmp");
    add_bitmap_file_to_textures(textures, "textures/flats/dirt.bmp");
    add_bitmap_file_to_textures(textures, "textures/sprites/voilaunefleur.bmp");
    add_bitmap_file_to_textures(textures, "textures/sprites/enemy_front.bmp");
    add_bitmap_file_to_textures(textures, "textures/sprites/enemy_front_firing_0.bmp");
    add_bitmap_file_to_textures(textures, "textures/sprites/enemy_front_firing_1.bmp");
    add_bitmap_file_to_textures(textures, "textures/sprites/enemy_front_firing_2.bmp");
    add_bitmap_file_to_textures(textures, "textures/sprites/enemy_front_firing_3.bmp");
    add_bitmap_file_to_textures(textures, "textures/sprites/enemy_left.bmp");
    add_bitmap_file_to_textures(textures, "textures/sprites/enemy_right.bmp");
    add_bitmap_file_to_textures(textures, "textures/sprites/enemy_back.bmp");
    add_bitmap_file_to_textures(textures, "textures/sprites/blackhole.bmp");
    add_bitmap_file_to_textures(textures, "textures/skybox/day.bmp");
    add_bitmap_file_to_textures(textures, "textures/skybox/night.bmp");
    add_bitmap_file_to_textures(textures, "textures/hud/sun.bmp");
    add_bitmap_file_to_textures(textures, "textures/hud/moon.bmp");
	add_bitmap_file_to_textures(textures, "textures/hud/health/ico1.bmp");
	add_bitmap_file_to_textures(textures, "textures/hud/health/ico2.bmp");
	add_bitmap_file_to_textures(textures, "textures/hud/health/ico3.bmp");
	add_bitmap_file_to_textures(textures, "textures/hud/bullet.bmp");
	add_bitmap_file_to_textures(textures, "textures/hud/faces/happy.bmp");
	add_bitmap_file_to_textures(textures, "textures/hud/faces/meh.bmp");
	add_bitmap_file_to_textures(textures, "textures/hud/faces/sad.bmp");
	add_bitmap_file_to_textures(textures, "textures/hud/faces/dead.bmp");
	add_bitmap_file_to_textures(textures, "textures/hud/faces/badass.bmp");
	add_bitmap_file_to_textures(textures, "textures/hud/faces/sehr_happy.bmp");
	add_bitmap_file_to_textures(textures, "textures/hud/faces/hurt.bmp");
	add_bitmap_file_to_textures(textures, "textures/wall_objects/lever_up.bmp");
	add_bitmap_file_to_textures(textures, "textures/wall_objects/lever_down.bmp");
	add_bitmap_file_to_textures(textures, "textures/wall_objects/flag.bmp");
	add_bitmap_file_to_textures(textures, "textures/weapons/dwa.bmp");
    add_bitmap_file_to_textures(textures, "textures/weapons/gun_1.bmp");
    add_bitmap_file_to_textures(textures, "textures/weapons/gun_2.bmp");
    add_bitmap_file_to_textures(textures, "textures/weapons/gun_3.bmp");
    add_bitmap_file_to_textures(textures, "textures/weapons/gun_firing.bmp");
    add_bitmap_file_to_textures(textures, "textures/weapons/gun_cooldown.bmp");
    add_bitmap_file_to_textures(textures, "textures/weapons/shotgun_1.bmp");
    add_bitmap_file_to_textures(textures, "textures/weapons/shotgun_cooldown.bmp");
    add_bitmap_file_to_textures(textures, "textures/weapons/shotgun_firing.bmp");
    add_bitmap_file_to_textures(textures, "textures/weapons/blackhole_destroyer.bmp");
    add_bitmap_file_to_textures(textures, "textures/sprites/gun.bmp");
    add_bitmap_file_to_textures(textures, "textures/sprites/shotgun.bmp");
    add_bitmap_file_to_textures(textures, "textures/sprites/vacuum.bmp");

    add_bitmap_file_to_textures(textures, "textures/explosions/explosion_1.bmp");
    add_bitmap_file_to_textures(textures, "textures/explosions/explosion_2.bmp");
    add_bitmap_file_to_textures(textures, "textures/explosions/explosion_3.bmp");
    add_bitmap_file_to_textures(textures, "textures/explosions/explosion_4.bmp");
    add_bitmap_file_to_textures(textures, "textures/explosions/explosion_5.bmp");
    add_bitmap_file_to_textures(textures, "textures/explosions/explosion_6.bmp");
    add_bitmap_file_to_textures(textures, "textures/explosions/explosion_7.bmp");
    add_bitmap_file_to_textures(textures, "textures/explosions/explosion_8.bmp");
    add_bitmap_file_to_textures(textures, "textures/explosions/explosion_9.bmp");
    add_bitmap_file_to_textures(textures, "textures/explosions/explosion_10.bmp");
    add_bitmap_file_to_textures(textures, "textures/explosions/explosion_11.bmp");
    add_bitmap_file_to_textures(textures, "textures/explosions/explosion_12.bmp");
    add_bitmap_file_to_textures(textures, "textures/explosions/explosion_13.bmp");
    add_bitmap_file_to_textures(textures, "textures/explosions/explosion_14.bmp");
    add_bitmap_file_to_textures(textures, "textures/explosions/explosion_15.bmp");
    add_bitmap_file_to_textures(textures, "textures/explosions/explosion_16.bmp");
    return (textures);
}
