#include "doom.h"
#include "map.h"
#include "debug.h"

t_map *allocate_map()
{
	int			i;
	int			j;
	t_walls*	walls;
	SDL_Surface *texture;
	t_map		*map;

	if (!(texture = SDL_LoadBMP("brickwall.bmp")))
		error_doom("there was an error while loading the BMP");

	if (!(map = (t_map*)malloc(sizeof(t_map))))
		error_doom("error: cannot allocate memory for struct map");

	if (!(map->sectors = (t_sectors*)malloc(sizeof(t_sectors))))
		error_doom("t_sectors");

	map->sectors->count = 1;  // todo: read shit
	if (!(map->sectors->items =
				(t_sector*)malloc(map->sectors->count * sizeof(t_sector))))
		error_doom("Can't allocate sectors");

	i = 0;
	while (i < map->sectors->count)
	{
		if (!(map->sectors->items->walls = (t_walls*)malloc(sizeof(t_walls))))
			error_doom("t_sectors");

		walls = map->sectors->items[i].walls;

		walls->count = 8;  // todo: read shit
		if (!(walls->items = (t_wall*)malloc(walls->count * sizeof(t_wall))))
			error_doom("Can't allocate walls");

		walls->items[0].segment = create_segment(0, 0, 5, 1);
		walls->items[1].segment = create_segment(5, 1, 4, 3);
		walls->items[2].segment = create_segment(4, 3, 5, 6);
		walls->items[3].segment = create_segment(5, 6, 8, 8);
		walls->items[4].segment = create_segment(8, 8, 9, 15);
		walls->items[5].segment = create_segment(9, 15, 3, 15);
		walls->items[6].segment = create_segment(3, 15, 4, 4);
		walls->items[7].segment = create_segment(4, 4, 0, 0);

		walls->items[0].height = 1.0;
		walls->items[1].height = 1.0;
		walls->items[2].height = 1.0;
		walls->items[3].height = 1.0;
		walls->items[4].height = 1.0;
		walls->items[5].height = 1.0;
		walls->items[6].height = 1.0;
		walls->items[7].height = 1.0;

		walls->items[0].texture = texture;
		walls->items[1].texture = texture;
		walls->items[2].texture = texture;
		walls->items[3].texture = texture;
		walls->items[4].texture = texture;
		walls->items[5].texture = texture;
		walls->items[6].texture = texture;
		walls->items[7].texture = texture;

		j = 0;
		while (j < walls->count)
		{
		    // todo: read shit
			j++;
		}
		i++;
	}

	return (map);
}

int		main (int ac, char **av)
{
	t_env		*e;
	t_map		*map;

	(void)ac;
	(void)av;
	if (!(e = (t_env*)malloc(sizeof(t_env))))
		error_doom("error: cannot allocate memory for struct env");
	if (!(e->p = (t_player*)malloc(sizeof(t_player))))
		error_doom("error: cannot allocate memory for struct player");
	if (!(e->doom = (t_sdl*)malloc(sizeof(t_sdl))))
		error_doom("error: cannot allocate memory for struct sdl");
	init_doom(e);

	map = allocate_map();
	e->p->weapons = allocate_weapons();

    if (ac > 1 && ft_strcmp(av[1], "debug") == 0)
    {
        e->debug_mode = t_true;
        e->debug = debug_init();
    }
	loop_doom(e, map);
	return (EXIT_SUCCESS);
}