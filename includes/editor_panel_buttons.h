#ifndef EDITOR_PANEL_BUTTONS_H
# define EDITOR_PANEL_BUTTONS_H

#include "editor.h"

typedef struct  s_btn_params
{
    SDL_Surface **selected;
    SDL_Surface *target;
    t_object    *object;
    t_enemy     *enemy;
    t_editor    *ed;
}               t_btn_params;

typedef struct			s_button
{
    t_rect			rect;
    void			(*f)(t_params params);
    t_btn_params    *params;
}						t_button;

typedef struct			s_buttons
{
    t_button			item;
    struct s_buttons    *next;
}						t_buttons;

void            add_button_to_list(t_buttons **list, t_button button);
void            free_buttons_list(t_buttons *list);
t_btn_params    *create_btn_params(
        SDL_Surface **selected, SDL_Surface *target, t_editor *ed);

void        toggle_lighting(t_params params);
void		toggle_skybox(t_params params);
void        create_object_in_map_state(t_params params);
void        create_enemy_in_map_state(t_params params);

void        create_object_in_sector(t_editor *ed, int mouse_x, int mouse_y);
void        create_enemy_in_sector(t_editor *ed, int mouse_x, int mouse_y);
void		try_sector_creation(t_editor *ed, int mouse_x, int mouse_y);

#endif
