#ifndef DOOMNUKEM_EDITOR_H
# define DOOMNUKEM_EDITOR_H

#include <unistd.h>
#include <stdio.h> // TO DELETE !!!
#include <math.h>

#include "SDL.h"
#include "doom.h"
#include "serialisation.h"
#include "editor_draw.h"
# include "textures.h"
# include "map.h"
# include "walls.h"
#include "default.h"
#include "surface_manipulation.h"
#include "editor_walls_nodes.h"

# define EDITOR_W 1600
# define EDITOR_H 600
# define EDITOR_W_H (EDITOR_W / 2)
# define EDITOR_H_H (EDITOR_H / 2)
# define EDITOR_ZOOM 30
# define CORNER_SIZE 10

typedef struct          s_editor t_editor;
typedef struct          s_wall_nodes t_wall_nodes;

typedef struct			s_sdl_editor
{
    SDL_Window			*window;
    SDL_Renderer		*renderer;
    SDL_Surface         *surface;
}						t_sdl_editor;

typedef struct			s_button
{
	t_rect				rect;
	void				(*f)(t_editor *ed, t_rect *rect);
}						t_button;

typedef struct			s_buttons
{
    int                 count;
	t_button			items[1];
}						t_buttons;

typedef struct          s_editor
{
	t_sdl_editor    sdl;
	char			*map_path;
    t_map			*map;
    t_textures      *textures;
    t_buttons       buttons;
    t_i_coords      text_pos;
    int             index;
    t_fonts			*fonts;
    t_wall_nodes    *selected_nodes;
    t_coords        *selected_player;
    t_wall			*selected_wall;
    t_enemy			*selected_enemy;
    t_object		*selected_object;
    t_sounds		*sounds;
}                       t_editor;

t_map		*create_map(t_textures *textures);
t_textures	*load_textures(void);
int         in_which_sector(t_i_coords pos, t_sectors sectors, t_editor *ed);
int         is_in_sector(t_i_coords pos, t_sector sector, t_editor *ed);
int	    	intersect_segment(t_i_coords p1, t_i_coords q1, t_i_coords p2, t_i_coords q2);
static int	orientation(t_i_coords p, t_i_coords q, t_i_coords r);
int			onSegment(t_i_coords p, t_i_coords q, t_i_coords r);s

void    mousedown_action(t_editor *ed, int mouse_x, int mouse_y);
void    mouseup_action(t_editor *ed, int mouse_x, int mouse_y);
enum e_bool click_on_panel(
        t_editor *ed, t_buttons *buttons, int mouse_x, int mouse_y);
enum e_bool click_on_nodes(t_editor *ed, t_linked_walls *linked_walls, int mouse_x, int mouse_y);
void            deal_with_clicked_wall(t_editor *ed, t_wall *wall);

#endif
