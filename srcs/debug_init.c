#include "doom.h"

void		debug_draw(t_sdl *debug, t_segment *s, Uint32 s_cnt, t_player *p)
{
	SDL_SetRenderDrawColor(debug->renderer, 0, 0, 0, 255);
	SDL_RenderClear(debug->renderer);
	ft_bzero(debug->surface->pixels, debug->surface->w * debug->surface->h * 4);
	debug_draw_grid(debug->surface);
	debug_draw_walls(debug->surface, s, s_cnt);
	debug_draw_player(debug->surface, p);
	print_surface(debug->renderer, debug->surface);
	SDL_RenderPresent(debug->renderer);
}

t_sdl		debug_init()
{
	t_sdl	debug;

	SDL_Init(SDL_INIT_VIDEO);
	debug.window = SDL_CreateWindow("debug", 0,
							  SDL_WINDOWPOS_UNDEFINED, DEBUG_W, DEBUG_H, SDL_WINDOW_OPENGL);
	if (debug.window == NULL)
		printf("Could not create window: %s\n", SDL_GetError());
	debug.renderer = SDL_CreateRenderer(debug.window, -1, 0);
	debug.texture = SDL_CreateTexture(debug.renderer,
			SDL_PIXELFORMAT_ARGB32, SDL_TEXTUREACCESS_TARGET,
			DEBUG_W, DEBUG_H);
	debug.surface = SDL_CreateRGBSurface(0, DEBUG_W, DEBUG_H,
			32, 0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);
	return (debug);
}
