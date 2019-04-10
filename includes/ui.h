#ifndef UI_H
# define UI_H

# include "SDL_ttf.h"
# include "struct_sdl.h"
# include "config.h"
# include "utils.h"
# include "map.h"
# include "doom.h"

void        ui_draw(SDL_Surface *surface, t_map *map, int fps, t_env *e);
SDL_Surface *write_text(char *font_path, int font_size, char *str, SDL_Colour color);
void        draw_on_screen(SDL_Surface *surface, SDL_Surface *text, t_coords location, enum e_bool force_alpha);

#endif
