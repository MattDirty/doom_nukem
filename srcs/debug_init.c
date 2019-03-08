#include "doom.h"

void		debug_init(t_segment *segments, Uint32 s_count)
{
	SDL_Window *window;
	SDL_Renderer *renderer;
	t_coords	player_pos;

	player_pos.x = 5;
	player_pos.y = 5;
	SDL_Init(SDL_INIT_VIDEO);
	window = SDL_CreateWindow("debug", SDL_WINDOWPOS_UNDEFINED,
							  SDL_WINDOWPOS_UNDEFINED, DEBUG_W, DEBUG_H, SDL_WINDOW_OPENGL);
	if (window == NULL)
		printf("Could not create window: %s\n", SDL_GetError());
	renderer = SDL_CreateRenderer(window, -1, 0);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
	debug_draw_grid(renderer);
	debug_draw_walls(renderer, segments, s_count);
	debug_draw_player(renderer, &player_pos);
	SDL_RenderPresent(renderer);
	SDL_Delay(5000); //should loop here, stays a delay because Windows.
	SDL_DestroyWindow(window);
	SDL_Quit();
}