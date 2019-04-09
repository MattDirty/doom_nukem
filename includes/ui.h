#ifndef UI_H
# define UI_H

# include "SDL_ttf.h"
# include "struct_sdl.h"
# include "config.h"
# include "utils.h"

void        ui_draw(t_sdl *sdl, t_config *op);

SDL_Surface *write_text(char *font_path, int font_size, char *str, SDL_Colour color);
void        draw_text(SDL_Surface *surface, SDL_Surface *font, t_coords location);
void draw_fps(SDL_Surface *surface, int fps, t_config *op);

#endif
