#include "debug.h"
#include "libft.h"
#include "surface_manipulation.h"
#include "default.h"

void		debug_draw(t_sdl *debug, t_map *map, t_player *p, t_config *op)
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
	debug_draw_player(debug->surface, p, op);
	print_surface(debug->renderer, debug->surface);
	SDL_RenderPresent(debug->renderer);
}
