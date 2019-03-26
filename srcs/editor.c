#include <stdio.h>

#include "doom.h"
#include "map.h"
#include "serialisation.h"

t_map		*create_map(t_textures *textures)
{
	int			i;
	int			j;
	t_walls*	walls;
	SDL_Surface *texture;
	t_map		*map;

	if (!(map = (t_map*)malloc(sizeof(t_map))))
		error_doom("error: cannot allocate memory for struct map");

	if (!(map->sectors = (t_sectors*)malloc(sizeof(t_sectors))))
		error_doom("t_sectors");

	map->sectors->count = 1;
	if (!(map->sectors->items =
				(t_sector*)malloc(map->sectors->count * sizeof(t_sector))))
		error_doom("Can't allocate sectors");

	i = 0;
	while (i < map->sectors->count)
	{
		if (!(map->sectors->items->walls = (t_walls*)malloc(sizeof(t_walls))))
			error_doom("t_sectors");

		walls = map->sectors->items[i].walls;

		walls->count = 10;
		if (!(walls->items = (t_wall*)malloc(walls->count * sizeof(t_wall))))
			error_doom("Can't allocate walls");

		walls->items[0].segment = create_segment(0, 0, 5, 1);
		walls->items[1].segment = create_segment(5, 1, 4, 3);
		walls->items[2].segment = create_segment(4, 3, 5, 6);
		walls->items[3].segment = create_segment(5, 6, 8, 8);
		walls->items[4].segment = create_segment(8, 8, 9, 15);
		walls->items[5].segment = create_segment(9, 15, 3, 15);
		walls->items[6].segment = create_segment(3, 15, 3.8, 6);
		walls->items[7].segment = create_segment(4, 4, 0, 0);
		walls->items[8].segment = create_segment(3.8, 6, 5, 6);
		walls->items[9].segment = create_segment(3.8, 6, 4, 4);
		walls->items[0].segment = create_segment(0, 0, 5, 1);

        find_texture_by_name(textures, "textures/walls/brickwall.bmp", &texture);

		j = 0;
		while (j < walls->count)
		{
		    walls->items[j].height = 1.0;
		    walls->items[j].texture = texture;
		    walls->items[j].portal = t_false;
			j++;
		}
		walls->items[8].portal = t_true;

		i++;
	}
    find_texture_by_name(textures, "textures/skybox/day.bmp", &texture);
    map->daysky = texture;
    find_texture_by_name(textures, "textures/skybox/night.bmp", &texture);
    map->nightsky = texture;
    map->daytime = t_true;
	return (map);
}

t_textures	*load_textures(void)
{
    t_textures	*textures;

    textures = (t_textures*)malloc(sizeof(textures));
    add_bitmap_file_to_textures(textures, "textures/weapons/dwa.bmp");
    add_bitmap_file_to_textures(textures, "textures/walls/brickwall.bmp");
    add_bitmap_file_to_textures(textures, "textures/sprites/voilaunefleur.bmp");
    add_bitmap_file_to_textures(textures, "textures/skybox/day.bmp");
    add_bitmap_file_to_textures(textures, "textures/skybox/night.bmp");
    return (textures);
}

int		main()
{
    t_map		*map;
    t_textures	*textures;

    textures = load_textures();
    map = create_map(textures);
    if (write_file("mabite.roflolilolmao", textures, map) < 0)
    {
        printf("Failure when writing file\n");
        return (-1);
    }

    printf("ta mere est une pute\n");
    return (0);
}
