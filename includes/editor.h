/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badhont <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 03:10:13 by badhont           #+#    #+#             */
/*   Updated: 2019/04/19 11:42:01 by badhont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOOMNUKEM_EDITOR_H
# define DOOMNUKEM_EDITOR_H

# include <unistd.h>
# include <math.h>

# include "SDL.h"
# include "doom.h"
# include "editor_draw.h"
# include "serialisation.h"
# include "textures.h"
# include "map.h"
# include "walls.h"
# include "collision.h"
# include "default.h"
# include "surface_manipulation.h"
# include "editor_walls_nodes.h"
# include "editor_panel.h"

# define EDITOR_W 1600
# define EDITOR_H 600
# define EDITOR_W_H (EDITOR_W / 3)
# define EDITOR_H_H (EDITOR_H / 2)
# define EDITOR_ZOOM 20
# define CORNER_SIZE 10

typedef	struct	s_wall_nodes t_wall_nodes;

typedef struct				s_sdl_editor
{
	SDL_Window			*window;
	SDL_Renderer		*renderer;
 	SDL_Surface			*surface;
}							t_sdl_editor;

typedef	struct				s_selected_elements
{
	t_wall_nodes		*nodes;
	t_coords			*p_spawn;
	t_enemy				*enemy;
	t_object			*object;
	t_sector			*sector;
    t_pickable			*pickable;
	t_wall              *wall;
}						t_selected_elements;

enum	e_editor_state
{
    e_null = 0,
    e_add_object,
    e_add_enemy,
    e_add_weapon,
    e_add_lever,
    e_add_sector,
    e_add_pickable
};

typedef struct				s_editor
{
	t_sdl_editor		sdl;
	char				*map_path;
    t_map				*map;
    t_textures      	*textures;
    t_sounds            *sounds;
    t_panel             panel;
    t_i_coords      	text_pos;
    t_i_coords			map_offset;
    int             	index;
    int					zoom;
    int 				multi_purpose_int;
    t_fonts				*fonts;
    SDL_Surface         **selected_sprite;
    enum e_editor_state state;
    t_coords			pos;
    void                (*state_func[7])
    (t_editor *ed, int mouse_x, int mouse_y);
	t_selected_elements	selected;
	t_selected_elements	dragged;
	t_linked_walls		*linked_walls;
	int					linked_walls_count;
	enum e_bool			map_is_updated;
}						t_editor;

t_map		*create_map(t_textures *textures);
t_textures	*load_textures(void);
void		editor_loop(t_editor *ed);

void    		mousedown_action(t_editor *ed, int mouse_x, int mouse_y);
void    		mouseup_action(t_editor *ed, int mouse_x, int mouse_y);
enum e_bool		click_on_nodes(t_editor *ed, t_linked_walls *linked_walls, int mouse_x, int mouse_y);
void			deal_with_clicked_wall(t_editor *ed, t_wall *wall);
void		quit_editor(t_editor *ed);
void		create_sub_lists(t_textures *textures, t_panel *panel);
t_sounds	*load_sounds(void);
t_fonts		*load_fonts(void);

#endif
