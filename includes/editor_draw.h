#ifndef EDITOR_DRAW_H
#define EDITOR_DRAW_H

# include "map.h"
# include "struct_sdl.h"
# include "editor.h"

# define WHITE 0xFFFFFFFF
# define RED 0xFFFF0000
# define PINK 0xFFFFAAAA
# define GREEN 0xFF00FF00


void		draw_editor(t_sdl_editor *sdl_ed, t_map *map);

#endif
