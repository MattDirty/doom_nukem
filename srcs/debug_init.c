#include "doom.h"

void		debug_draw(SDL_Renderer *r, t_segment *s, Uint32 s_cnt, t_player *p)
{
	SDL_SetRenderDrawColor(r, 0, 0, 0, 255);
	SDL_RenderClear(r);
	debug_draw_grid(r);
	debug_draw_walls(r, s, s_cnt);
	debug_draw_player(r, p);
	SDL_RenderPresent(r);
}

SDL_Renderer	*debug_init(t_segment *segments, Uint32 s_count, t_player *p)
{
	SDL_Window *window;
	SDL_Renderer *renderer;

	SDL_Init(SDL_INIT_VIDEO);
	window = SDL_CreateWindow("debug", SDL_WINDOWPOS_UNDEFINED,
							  SDL_WINDOWPOS_UNDEFINED, DEBUG_W, DEBUG_H, SDL_WINDOW_OPENGL);
	if (window == NULL)
		printf("Could not create window: %s\n", SDL_GetError());
	renderer = SDL_CreateRenderer(window, -1, 0);
	debug_draw(renderer, segments, s_count, p);
	return (renderer);
}
