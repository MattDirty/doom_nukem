#include <stdio.h>

#include "doom.h"
#include "map.h"
#include "serialisation.h"

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
			error_doom("t_sectors");

        if (find_texture_by_name(
                textures,
                "textures/flats/grass.bmp",
                &map->sectors->items[i].floor) < 0)
            error_doom("could not find grass");
        if (find_texture_by_name(
                textures,
                "textures/flats/dirt.bmp",
                &map->sectors->items[i].ceil) < 0)
            error_doom("could not find dirt");
        map->sectors->items[i].open_sky = t_false;
        map->sectors->items[2].open_sky = t_true;
        map->sectors->items[i].objects =
                (t_objects*)malloc(sizeof(t_objects));
        map->sectors->items[i].objects->count = 0;
        map->sectors->items[i].objects->items = NULL;
        if (i == 1000)
        {
            map->sectors->items[i].objects->count = 1;
            map->sectors->items[i].objects->items = (t_object*)malloc(
                    sizeof(t_object) * map->sectors->items[i].objects->count);
            map->sectors->items[i].objects->items[0].x = 7;
            map->sectors->items[i].objects->items[0].y = 5;
            if (find_texture_by_name(
                    textures,
                    "textures/sprites/voilaunefleur.bmp",
                    &map->sectors->items[i].objects->items[0].sprite) < 0)
                error_doom("could not find voilaunefleur.bmp");
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
		    walls->items[j]->height = 1.0;
		    walls->items[j]->type = e_wall;
		    if (i == 1)
            {
                if (find_texture_by_name(
                        textures,
                        "textures/walls/stones.bmp",
                        &walls->items[j]->pointer.texture) < 0)
                    error_doom("could not find stones");
            }
		    else
            {
                if (find_texture_by_name(
                        textures,
                        "textures/walls/brickwall2.bmp",
                        &walls->items[j]->pointer.texture) < 0)
                            error_doom("could not find brickwall2");
            }
			j++;
		}
		if (i == 0)
		{
			walls->items[1]->type = e_portal;
			walls->items[1]->pointer.sector.sector1 = &map->sectors->items[0];
			walls->items[1]->pointer.sector.sector2 = &map->sectors->items[1];
			map->sectors->items[i].light = 0x32000000;
		}
		else if (i == 1)
        {
			walls->items[1]->type = e_portal;
			walls->items[1]->pointer.sector.sector1 = &map->sectors->items[1];
			walls->items[1]->pointer.sector.sector2 = &map->sectors->items[2];
			free(walls->items[3]);
			walls->items[3] = map->sectors->items[0].walls->items[1];
			map->sectors->items[i].light = 0x64000000;
		}
		else
		{
			free(walls->items[3]);
			walls->items[3] = map->sectors->items[1].walls->items[1];
			map->sectors->items[i].light = 0x96000000;
		}
		i++;
	}
    if (find_texture_by_name(textures, "textures/skybox/day.bmp", &map->daysky) < 0)
        error_doom("could not find day");
    if (find_texture_by_name(textures, "textures/skybox/night.bmp", &map->nightsky) < 0)
        error_doom("could not find night");
    if (find_texture_by_name(textures, "textures/hud/sun.bmp", &map->hud.sun) < 0)
        error_doom("could not find sun");
    if (find_texture_by_name(textures, "textures/hud/moon.bmp", &map->hud.moon) < 0)
        error_doom("could not find moon");
	if (find_texture_by_name(textures, "textures/hud/health/ico1.bmp", &map->hud.cross[0]) < 0)
		error_doom("could not find health_ico1");
	if (find_texture_by_name(textures, "textures/hud/health/ico2.bmp", &map->hud.cross[1]) < 0)
		error_doom("could not find health_ico2");
	if (find_texture_by_name(textures, "textures/hud/health/ico3.bmp", &map->hud.cross[2]) < 0)
		error_doom("could not find health_ico3");
    if (find_texture_by_name(textures, "textures/hud/bullet.bmp", &map->hud.bullet) < 0)
        error_doom("could not find bullet");
	if (find_texture_by_name(textures, "textures/hud/faces/happy.bmp", &map->hud.happy_face) < 0)
		error_doom("could not find happy face");
	if (find_texture_by_name(textures, "textures/hud/faces/meh.bmp", &map->hud.meh_face) < 0)
		error_doom("could not find meh face");
	if (find_texture_by_name(textures, "textures/hud/faces/sad.bmp", &map->hud.sad_face) < 0)
		error_doom("could not find sad face");
	if (find_texture_by_name(textures, "textures/hud/faces/dead.bmp", &map->hud.dead_face) < 0)
		error_doom("could not find dead face");
	if (find_texture_by_name(textures, "textures/hud/faces/badass.bmp", &map->hud.badass_face) < 0)
		error_doom("could not find badass face");
	if (find_texture_by_name(textures, "textures/hud/faces/sehr_happy.bmp", &map->hud.sehr_happy_face) < 0)
		error_doom("could not find sehr happy face");
	if (find_texture_by_name(textures, "textures/hud/faces/hurt.bmp", &map->hud.hurt_face) < 0)
		error_doom("could not find hurt face");
    map->daytime = t_true;
	return (map);
}

t_textures	*load_textures(void)
{
    t_textures	*textures;

    if (!(textures = (t_textures*)malloc(sizeof(t_textures))))
        error_doom("could not allocate textures");
    textures->first = NULL;
    if (add_bitmap_file_to_textures(textures, "textures/weapons/dwa.bmp") < 0)
        error_doom("could not load dwa");
    if (add_bitmap_file_to_textures(textures, "textures/walls/stones.bmp") < 0)
        error_doom("could not load stones");
    if (add_bitmap_file_to_textures(textures, "textures/walls/brickwall2.bmp") < 0)
        error_doom("could not load brickwall2");
    if (add_bitmap_file_to_textures(textures, "textures/flats/grass.bmp") < 0)
        error_doom("could not load grass");
    if (add_bitmap_file_to_textures(textures, "textures/flats/dirt.bmp") < 0)
        error_doom("could not load dirt");
    if (add_bitmap_file_to_textures(textures, "textures/sprites/voilaunefleur.bmp") < 0)
        error_doom("could not load voilaunefleur");
    if (add_bitmap_file_to_textures(textures, "textures/skybox/day.bmp") < 0)
        error_doom("could not load day");
    if (add_bitmap_file_to_textures(textures, "textures/skybox/night.bmp") < 0)
        error_doom("could not load night");
    if (add_bitmap_file_to_textures(textures, "textures/hud/sun.bmp") < 0)
        error_doom("could not load sun");
    if (add_bitmap_file_to_textures(textures, "textures/hud/moon.bmp") < 0)
        error_doom("could not load moon");
	if (add_bitmap_file_to_textures(textures, "textures/hud/health/ico1.bmp") < 0)
		error_doom("could not load health_ico1");
	if (add_bitmap_file_to_textures(textures, "textures/hud/health/ico2.bmp") < 0)
		error_doom("could not load health_ico2");
	if (add_bitmap_file_to_textures(textures, "textures/hud/health/ico3.bmp") < 0)
		error_doom("could not load health_ico3");
	if (add_bitmap_file_to_textures(textures, "textures/hud/bullet.bmp") < 0)
		error_doom("could not load bullet");
	if (add_bitmap_file_to_textures(textures, "textures/hud/faces/happy.bmp") < 0)
		error_doom("could not load happy face");
	if (add_bitmap_file_to_textures(textures, "textures/hud/faces/meh.bmp") < 0)
		error_doom("could not load meh face");
	if (add_bitmap_file_to_textures(textures, "textures/hud/faces/sad.bmp") < 0)
		error_doom("could not load sad face");
	if (add_bitmap_file_to_textures(textures, "textures/hud/faces/dead.bmp") < 0)
		error_doom("could not load dead face");
	if (add_bitmap_file_to_textures(textures, "textures/hud/faces/badass.bmp") < 0)
		error_doom("could not load badass face");
	if (add_bitmap_file_to_textures(textures, "textures/hud/faces/sehr_happy.bmp") < 0)
		error_doom("could not load sehr happy face");
	if (add_bitmap_file_to_textures(textures, "textures/hud/faces/hurt.bmp") < 0)
		error_doom("could not load hurt face");
    return (textures);
}

int		main()
{
    t_map		*map;
    t_textures	*textures;

    textures = load_textures();
    map = create_map(textures);
	write_file("mabite.roflolilolmao", textures, map);
	printf("ta mere est une pute\n"); //j'aimerais que la norminette m'engueule.
    return (0);
}
