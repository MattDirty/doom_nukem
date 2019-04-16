#ifndef EDITOR_DRAW_H
#define EDITOR_DRAW_H

# include "map.h"
# include "struct_sdl.h"
# include "editor.h"

typedef struct s_editor t_editor;
typedef struct s_buttons t_buttons;

# define DRAW_MAP_X EDITOR_W_H / 3
# define DRAW_MAP_Y EDITOR_H_H

# define WHITE 0xFFFFFFFF
# define RED 0xFFFF0000
# define PINK 0xFFFFAAAA
# define GREEN 0xFF00FF00
# define BLUE 0xFF0000FF
# define L_BLUE 0xFF8888FF
# define YELLOW 0xFFF4EE42
# define BACKGROUND_COLOR 0xFF756F68
# define YELLOW 0xFFF4EE42
# define PLAYER_COLOR WHITE

void draw_background(t_editor *ed);
void draw_panel_back(SDL_Surface *surface);
void draw_editor(t_editor *ed);
void draw_panel(t_editor *ed);

#endif
