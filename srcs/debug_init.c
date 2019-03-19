#include "debug.h"
#include "libft.h"
#include "surface_manipulation.h"
#include "default.h"

void		debug_draw(t_sdl *debug, t_map *map, t_player *p)
{
    int i;

	SDL_SetRenderDrawColor(debug->renderer, 0, 0, 0, 255);
	SDL_RenderClear(debug->renderer);
	ft_bzero(debug->surface->pixels, debug->surface->w * debug->surface->h * 4);
	debug_draw_grid(debug->surface);

	i = 0;
	while (i < map->sectors->count)
	{
		debug_draw_walls(debug->surface, map->sectors->items[i].walls);
		i++;
	}
	debug_draw_player(debug->surface, p);
	print_surface(debug->renderer, debug->surface);
	SDL_RenderPresent(debug->renderer);
}

t_sdl debug_init()
{
    t_sdl debug;

    debug.window = SDL_CreateWindow("debug", 0,
    		SDL_WINDOWPOS_UNDEFINED, DEBUG_W, DEBUG_H, SDL_WINDOW_OPENGL);
    if (debug.window == NULL)
        printf("Could not create window: %s\n", SDL_GetError());
    debug.renderer = SDL_CreateRenderer(debug.window, -1, 0);
    debug.texture = SDL_CreateTexture(debug.renderer,
    		SDL_PIXELFORMAT_ARGB32, SDL_TEXTUREACCESS_TARGET,
                                      DEBUG_W, DEBUG_H);
    debug.surface = SDL_CreateRGBSurface(0, DEBUG_W, DEBUG_H,
    		32, MASK_RED, MASK_GREEN, MASK_BLUE, MASK_ALPHA);
    return (debug);
}
