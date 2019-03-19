#ifndef DOOMNUKEM_DEBUG_H
#define DOOMNUKEM_DEBUG_H

#include "SDL.h"
#include "walls.h"
#include "player.h"
#include "struct_sdl.h"

void		debug_draw_walls(SDL_Surface *surface, t_walls *walls);
void		debug_draw_grid(SDL_Surface *surface);
void		debug_draw_player(SDL_Surface *surface, t_player *p);
void		debug_draw(t_sdl *debug, t_map *map, t_player *p);

t_sdl		debug_init();

#endif
