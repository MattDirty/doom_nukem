#ifndef EDITOR_DRAW_H
#define EDITOR_DRAW_H

# include "map.h"
# include "struct_sdl.h"
# include "editor.h"

# define DRAW_MAP_X (EDITOR_W_H / 3)
# define DRAW_MAP_Y EDITOR_H_H
# define panel_X (EDITOR_W - 2 * DRAW_MAP_X)
# define panel_Y 0

# define WHITE 0xFFFFFFFF
# define RED 0xFFFF0000
# define PINK 0xFFFFAAAA
# define GREEN 0xFF00FF00
# define BLUE 0xFF0000FF
# define DARK_BLUE 0xFF073784
# define L_BLUE 0xFF8888FF

void click_on_panel(
        t_editor *ed, t_buttons *buttons, int mouse_x, int mouse_y);
void draw_panel(t_editor *ed);
void draw_editor(t_editor *ed);
void draw_save_button(
        TTF_Font *font, SDL_Surface *target, t_buttons *buttons, int i);

#endif
