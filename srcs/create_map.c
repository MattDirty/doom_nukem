/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badhont <badhont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 19:36:17 by badhont           #+#    #+#             */
/*   Updated: 2019/04/11 19:45:54 by badhont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "SDL.h"
//#include "editor.h"
#include "doom.h"
//#include "map.h"
//#include "serialisation.h"
//#include "libft.h"
//#include "editor_draw.h"

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

	map->sectors->count = 3;
	if (!(map->sectors->items =
				(t_sector*)malloc(map->sectors->count * sizeof(t_sector))))
		error_doom("Can't allocate sectors");

	i = 0;
	while (i < map->sectors->count)
	{
		if (!(map->sectors->items[i].walls = (t_walls*)malloc(sizeof(t_walls))))
			error_doom("t_walls");

        find_texture_by_name(textures, "textures/flats/grass.bmp", &map->sectors->items[i].floor);
        find_texture_by_name(textures, "textures/flats/dirt.bmp", &map->sectors->items[i].ceil);
        map->sectors->items[i].open_sky = t_false;
        map->sectors->items[2].open_sky = t_true;
        map->sectors->items[i].objects = (t_objects*)malloc(sizeof(t_objects));
        map->sectors->items[i].objects->count = 0;
        map->sectors->items[i].objects->items = NULL;
       // if (i == 0)
        //{
            map->sectors->items[i].objects->count = 3;
            map->sectors->items[i].objects->items = (t_object*)malloc(
                    sizeof(t_object) * map->sectors->items[i].objects->count);
            map->sectors->items[i].objects->items[0].x = 1;
            map->sectors->items[i].objects->items[0].y = i * 4 + 2;;
            map->sectors->items[i].objects->items[0].z = 0;
            map->sectors->items[i].objects->items[0].horizontal_size = 0.25;
            map->sectors->items[i].objects->items[0].vertical_size = 0.25;
            find_texture_by_name(textures, "textures/sprites/voilaunefleur.bmp", &map->sectors->items[i].objects->items[0].sprite);
        //}
        map->sectors->items[i].objects->items[1].x = 2;
        map->sectors->items[i].objects->items[1].y = i * 4 + 2;
        map->sectors->items[i].objects->items[1].z = 0;
        map->sectors->items[i].objects->items[1].horizontal_size = 0.25;
        map->sectors->items[i].objects->items[1].vertical_size = 0.5;
        map->sectors->items[i].objects->items[2].x = 3;
        map->sectors->items[i].objects->items[2].y = i * 4 + 2;
        map->sectors->items[i].objects->items[2].z = 0;
        map->sectors->items[i].objects->items[2].horizontal_size = 0.25;
        map->sectors->items[i].objects->items[2].vertical_size = 1;
        find_texture_by_name(textures, "textures/sprites/voilaunefleur.bmp", &map->sectors->items[i].objects->items[1].sprite);
        find_texture_by_name(textures,"textures/sprites/voilaunefleur.bmp", &map->sectors->items[i].objects->items[2].sprite);

        map->sectors->items[i].enemies = (t_enemies*)malloc(sizeof(t_enemies));
        map->sectors->items[i].enemies->count = 1;
        if (!(map->sectors->items[i].enemies->items = (t_enemy*)malloc(
                sizeof(t_enemy) * map->sectors->items[i].enemies->count)))
            error_doom("Couldn't allocate enemies\n");

        if (!(map->sectors->items[i].enemies->items[0].object = (t_object *)
                malloc(sizeof(t_object))))
            error_doom("couldn't allocate enemies objects");
        map->sectors->items[i].enemies->items[0].object->x = 1;
        map->sectors->items[i].enemies->items[0].object->y = i * 4 + 1;;
        map->sectors->items[i].enemies->items[0].object->z = 0;
        map->sectors->items[i].enemies->items[0].object->horizontal_size = 1;
        map->sectors->items[i].enemies->items[0].object->vertical_size = 1;
        map->sectors->items[i].enemies->items[0].life_remaining = 100;
		map->sectors->items[i].enemies->items[0].time_in_death = -1;
		map->sectors->items[i].enemies->items[0].to_destroy = t_false;
        map->sectors->items[i].enemies->items[0].heading = 0;
        find_texture_by_name(textures,"textures/sprites/enemy_front.bmp", &map->sectors->items[i].enemies->items[0].front);
        map->sectors->items[i].enemies->items[0].object->sprite =
                map->sectors->items[i].enemies->items[0].front;
        find_texture_by_name(textures,"textures/sprites/enemy_side.bmp", &map->sectors->items[i].enemies->items[0].side);
        if (i == 1)
            map->sectors->items[i].enemies->items[0].heading = ft_degtorad(90);
        if (i == 2)
        {
            find_texture_by_name(textures,"textures/sprites/blackhole.bmp", &map->sectors->items[i].enemies->items[0].front);
            map->sectors->items[i].enemies->items[0].object->sprite =
                    map->sectors->items[i].enemies->items[0].front;
            find_texture_by_name(textures,"textures/sprites/blackhole.bmp", &map->sectors->items[i].enemies->items[0].side);
            map->sectors->items[i].enemies->items[0].heading = ft_degtorad(180);
        }

		walls = map->sectors->items[i].walls;
		find_texture_by_name(
				textures,
				"textures/walls/stones.bmp",
				&map->sectors->items[1].floor);
		find_texture_by_name(
				textures,
				"textures/flats/dirt.bmp",
				&map->sectors->items[2].floor);
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
		    walls->items[j]->to_infinity = t_false;
            walls->items[j]->wall_offset = 0;
		    if (i == 1)
                find_texture_by_name(textures, "textures/walls/stones.bmp", &walls->items[j]->texture);
		    else
                find_texture_by_name(textures, "textures/walls/brickwall2.bmp", &walls->items[j]->texture);
			j++;
		}
        if (i == 0)
        {
            if (!(walls->items[2]->wall_object = malloc(sizeof(t_wall_object))))
                error_doom("can't alloc wall object");
            walls->items[2]->wall_object->offset_on_wall = 2;
            walls->items[2]->wall_object->z = 0.3;
            walls->items[2]->wall_object->size = 0.7;
            find_texture_by_name(
                    textures,
                    "textures/wall_objects/flag.bmp",
                    &walls->items[2]->wall_object->texture);
        }
        if (i == 1)
        {
            if (!(walls->items[2]->lever = malloc(sizeof(t_lever))))
                error_doom("can't alloc wall lever");
            if (!(walls->items[2]->lever->wall_object =
                    malloc(sizeof(t_wall_object))))
                error_doom("can't alloc wall lever object");
            walls->items[2]->lever->activated = t_false;
            walls->items[2]->lever->wall_object->offset_on_wall = 2;
            walls->items[2]->lever->wall_object->z = 0.25;
            walls->items[2]->lever->wall_object->size = 0.5;
            walls->items[2]->lever->door = walls->items[1];
            find_texture_by_name(
                    textures,
                    "textures/wall_objects/lever_up.bmp",
                    &walls->items[2]->lever->wall_object->texture);
            find_texture_by_name(
                    textures,
                    "textures/wall_objects/lever_up.bmp",
                    &walls->items[2]->lever->up_texture);
            find_texture_by_name(
                    textures,
                    "textures/wall_objects/lever_down.bmp",
                    &walls->items[2]->lever->down_texture);
        }
		if (i == 0)
		{
			walls->items[1]->type = e_portal;
			walls->items[1]->links.sector1 = &map->sectors->items[0];
			walls->items[1]->links.sector2 = &map->sectors->items[1];
			map->sectors->items[i].light = 0x32FF0000;
		}
		else if (i == 1)
        {
			walls->items[1]->type = e_transparent_wall;
			walls->items[1]->links.sector1 = &map->sectors->items[1];
			walls->items[1]->links.sector2 = &map->sectors->items[2];
            find_texture_by_name(textures, "textures/walls/fence.bmp",
                    &walls->items[1]->texture);
            free(walls->items[3]);
			walls->items[3] = map->sectors->items[0].walls->items[1];
			map->sectors->items[i].light = 0x64000000;
		}
		else
		{
		    walls->items[1]->to_infinity = t_true;
            walls->items[1]->type = e_transparent_wall;
            walls->items[1]->links.sector1 = &map->sectors->items[2];
            walls->items[1]->links.sector2 = &map->sectors->items[2];
            find_texture_by_name(textures, "textures/walls/fence.bmp", &walls->items[1]->texture);
            free(walls->items[3]);
			walls->items[3] = map->sectors->items[1].walls->items[1];
			map->sectors->items[i].light = 0x96000000;
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
    map->daytime = t_true;
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
    add_bitmap_file_to_textures(textures, "textures/flats/grass.bmp");
    add_bitmap_file_to_textures(textures, "textures/flats/dirt.bmp");
    add_bitmap_file_to_textures(textures, "textures/sprites/voilaunefleur.bmp");
    add_bitmap_file_to_textures(textures, "textures/sprites/enemy_front.bmp");
    add_bitmap_file_to_textures(textures, "textures/sprites/enemy_side.bmp");
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
    return (textures);
}
