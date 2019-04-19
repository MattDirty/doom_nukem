/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_panel_buttons.h                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badhont <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 04:52:25 by badhont           #+#    #+#             */
/*   Updated: 2019/04/19 11:31:22 by badhont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EDITOR_PANEL_BUTTONS_H
# define EDITOR_PANEL_BUTTONS_H

# include "editor.h"

typedef	struct			s_btn_params
{
	SDL_Surface			**selected;
	SDL_Surface			*target;
	t_object			*object;
	t_enemy				*enemy;
	t_pickable			*pickable;
	t_editor			*ed;
}						t_btn_params;

typedef struct			s_button
{
	t_rect				rect;
	void				(*f)(t_params params);
	t_btn_params		*params;
}						t_button;

typedef struct			s_buttons
{
	t_button			item;
	struct s_buttons	*next;
}						t_buttons;

void					add_button_to_list(t_buttons **list,
							t_button button);
void					free_buttons_list(t_buttons *list);
t_btn_params			*create_btn_params(SDL_Surface **selected,
							SDL_Surface *target, t_editor *ed);

void					create_light_btn(TTF_Font *font, SDL_Surface *target,
							Uint32 light_color, t_editor *ed);
void					create_sky_toggle_btn(TTF_Font *font,
							SDL_Surface *target, t_editor *ed, int *y);
void					toggle_lighting(t_params params);
void					toggle_skybox(t_params params);
void					create_object_in_map_state(t_params params);
void					create_enemy_in_map_state(t_params params);

void					create_object_in_sector(t_editor *ed,
							int mouse_x, int mouse_y);
void					create_enemy_in_sector(t_editor *ed,
							int mouse_x, int mouse_y);
void					create_pickable_in_sector(t_editor *ed,
							int mouse_x, int mouse_y);
void					try_sector_creation(t_editor *ed,
							int mouse_x, int mouse_y);
void					try_lever_creation(t_editor *ed,
							int mouse_x, int mouse_y);

void					create_save_button(TTF_Font *font, SDL_Surface *target,
							t_panel *panel, t_editor *ed);
void					add_weapon_btn(t_editor *ed, TTF_Font *font,
							SDL_Surface *target, int *y);

void					remove_selected_pickable(t_editor *ed);
void					remove_selected_object(t_params params);

void					width_btn(t_editor *ed, TTF_Font *font,
							SDL_Surface *target, int *y);
void					height_btn(t_editor *ed, TTF_Font *font,
							SDL_Surface *target, int *y);
void					z_btn(t_editor *ed, TTF_Font *font, SDL_Surface *target,
							int *y);
void					remove_btn(t_editor *ed, TTF_Font *font,
							SDL_Surface *target, int *y);

void					change_window_in_wall_button(t_editor *ed, int *y);
void					change_wall_in_window_button(t_editor *ed, int *y);
void					create_transform_portal_to_door_button(t_editor *ed,
							int *y);
void					create_transform_door_to_portal_button(t_editor *ed,
							int *y);
void 					create_add_door_lever_button(t_editor *ed, int *y);
void 					add_object_btn(t_editor *ed, TTF_Font *font,
							SDL_Surface *target, int *y);
void 					change_object_height(t_params params);
void 					change_object_z(t_params params);
void 					change_object_width(t_params params);
void					hp_btn(t_editor *ed, TTF_Font *font,
							SDL_Surface *target, int *y);
void					change_enemy_hp(t_params params);
void 					add_enemy_btn(t_editor *ed, TTF_Font *font,
							SDL_Surface *target, int *y);
void					create_new_sector_button(t_editor *ed, int *y);
void					remove_selected_enemy(t_editor *ed);

#endif
