#ifndef DOOMNUKEM_UI_H
# define DOOMNUKEM_UI_H

# include "struct_sdl.h"
# include "config.h"

void        ui_draw(t_sdl *sdl, t_config *op);
void        draw_crosshair(SDL_Surface *surface, t_config *op, Uint32 color);

#endif
