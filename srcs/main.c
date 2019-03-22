#include "doom.h"
#include "map.h"
#include "debug.h"
#include "config.h"
#include "default.h"

t_sdl       init_sdl(Uint32 w, Uint32 h, Uint32 fullscreen, char *name)
{
    t_sdl   sdl;

    if (fullscreen)
        fullscreen = SDL_WINDOW_FULLSCREEN_DESKTOP;
    if (!(sdl.window = SDL_CreateWindow(name, 0, 0,
            w, h, fullscreen)))
        error_doom("Could not create window.");
    if (!(sdl.renderer = SDL_CreateRenderer(sdl.window, -1, 0)))
        error_doom("Could not create renderer");
    if (!(sdl.texture = SDL_CreateTexture(sdl.renderer,
            SDL_PIXELFORMAT_ARGB32, SDL_TEXTUREACCESS_TARGET,
            w, h)))
        error_doom("Could not create texture.");
    if (!(sdl.surface = SDL_CreateRGBSurface(0, w, h,
            32, MASK_RED, MASK_GREEN, MASK_BLUE, MASK_ALPHA)))
        error_doom("Could not create surface.");
    return (sdl);
}

t_map *allocate_map(void)
{
	int			i;
	int			j;
	t_walls*	walls;
    SDL_Surface *texture;
    SDL_Surface *texture2;
	t_map		*map;

	if (!(texture = SDL_LoadBMP("textures/walls/brickwall.bmp")))
		error_doom("there was an error while loading the BMP");

    if (!(texture2 = SDL_LoadBMP("brickwall2.bmp")))
        error_doom("there was an error while loading the BMP");

	if (!(map = (t_map*)malloc(sizeof(t_map))))
		error_doom("error: cannot allocate memory for struct map");

	if (!(map->sectors = (t_sectors*)malloc(sizeof(t_sectors))))
		error_doom("t_sectors");

	map->sectors->count = 2;  // todo: read shit
    if (!(map->sectors->items =
				(t_sector*)malloc(map->sectors->count * sizeof(t_sector))))
		error_doom("Can't allocate sectors");

    i = 0;
	while (i < map->sectors->count)
	{
        if (!(map->sectors->items[i].walls = (t_walls*)malloc(sizeof(t_walls))))
			error_doom("t_sectors");

		walls = map->sectors->items[i].walls;

		walls->count = 4;  // todo: read shit

        if (!(walls->items = (t_wall*)malloc(walls->count * sizeof(t_wall))))
			error_doom("Can't allocate walls");

		walls->items[0].segment = create_segment(0, 0 + i * 4, 0, 4 + i * 4);
		walls->items[1].segment = create_segment(0, 4 + i * 4, 4, 4 + i * 4);
		walls->items[2].segment = create_segment(4, 4 + i * 4, 4, 0 + i * 4);
		walls->items[3].segment = create_segment(4, 0 + i * 4, 0, 0 + i * 4);

		j = 0;
		while (j < walls->count)
		{
		    // todo: read shit
		    walls->items[j].height = 1.0;
		    walls->items[j].type = wall;
		    if (i == 0)
    		    walls->items[j].pointer.texture = texture;
		    else
		        walls->items[j].pointer.texture = texture2;
			j++;
		}
		if (i == 0)
        {
		    walls->items[1].type = portal;
		    walls->items[1].pointer.sector.sector1 = &map->sectors->items[0];
            walls->items[1].pointer.sector.sector2 = &map->sectors->items[1];
        }
		else
        {
            walls->items[3].segment = create_segment(8, 8, 10, 10);
            walls->items[3].type = portal;
            walls->items[3].pointer.sector.sector1 = &map->sectors->items[1];
            walls->items[3].pointer.sector.sector2 = &map->sectors->items[0];
        }
		i++;
	}
	if (!(map->daysky = SDL_LoadBMP("textures/skybox/day.bmp")))
		error_doom("error: cannot load day sky texture");
	if (!(map->nightsky = SDL_LoadBMP("textures/skybox/night.bmp")))
		error_doom("error: cannot load day sky texture");
	map->daytime = t_true;
	return (map);
}

int		main (int ac, char **av)
{
	t_env		e;

	e.op = load_config();
	if (ac > 1 && ft_strcmp(av[1], "debug") == 0)
		e.debug_mode = t_true;
	else
		e.debug_mode = t_false;
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		error_doom("error: cannot run SDL");
	e.doom = init_sdl(e.op.win_w, e.op.win_h, e.op.fullscreen, "Doom_Nukem");
	init_doom(&e);
	e.map = allocate_map();
    e.p.weapons = allocate_weapons();
    if (e.debug_mode)
		e.debug = init_sdl(DEBUG_W, DEBUG_H, 0, "debug");
	loop_doom(&e);
	return (EXIT_SUCCESS);
}