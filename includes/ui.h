#ifndef UI_H
# define UI_H

# include "SDL_ttf.h"
# include "struct_sdl.h"
# include "config.h"
# include "utils.h"
# include "map.h"
# include "doom.h"

void        draw_sun_or_moon(SDL_Surface *surface, t_map *map, t_config *op);
void        draw_crosshair(SDL_Surface *surface, t_config *op, Uint32 color);
void        draw_fps(TTF_Font *font, SDL_Surface *surface, int fps, t_config *op);
enum e_bool cross_index(double ms_since_update, t_params i);
void        draw_health(t_env *e);
void        draw_ammo(t_env *e, SDL_Surface *bullet, int ammo);
void        ui_draw(SDL_Surface *surface, t_map *map, int fps, t_env *e);
SDL_Surface *write_text(TTF_Font *font, char *str, SDL_Colour color);
void        draw_on_screen(SDL_Surface *surface, SDL_Surface *text, t_coords location, enum e_bool force_alpha);
void        rotate_and_draw(SDL_Surface *surface, SDL_Surface *text, t_coords location, enum e_bool force_alpha);

#endif
