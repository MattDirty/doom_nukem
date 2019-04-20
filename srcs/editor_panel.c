/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_panel.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfatton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/20 07:27:23 by lfatton           #+#    #+#             */
/*   Updated: 2019/04/20 07:27:26 by lfatton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"
#include "editor_panel.h"
#include "editor_draw.h"
#include "editor_panel_buttons.h"
#include "in_which_sector.h"
#include "ui.h"
#include "sounds.h"

void	draw_panel_back(SDL_Surface *surface)
{
	t_rect	panel;

	panel = create_rect(0, 0, PANEL_W - 1, EDIT_H - 1);
	draw_rect(surface, &panel, WHITE);
	fill_rect(surface, &panel, PANEL_BACKGROUND, e_false);
}

void	write_panel_state(t_editor *ed, char *state_str)
{
	SDL_Surface *state;

	state = write_text(ed->fonts->vcr40, state_str,
			(SDL_Colour){255, 255, 255, 255});
	draw_on_screen(ed->panel.surface, state,
			(t_i_coords){PANEL_W / 2 - state->w / 2, 10}, e_false);
	SDL_FreeSurface(state);
}

void	save_editor(t_params params)
{
	t_btn_params	*ptr;

	ptr = (t_btn_params *)params;
	ptr->ed->map->player_spawn_index = sector_index(ptr->ed->map->sectors,
			in_which_sector(ptr->ed->map->spawn, ptr->ed->map->sectors));
	Mix_PlayChannel(-1, ptr->ed->sounds->mip_mep, 0);
	write_file(ptr->ed->map_path, ptr->ed->textures, ptr->ed->map);
	ptr->ed->map_is_updated = e_true;
}

void	draw_panel(t_editor *ed)
{
	draw_panel_back(ed->panel.surface);
	if (ed->selected.wall)
		editor_draw_panel_walls(ed);
	else if (ed->selected.enemy)
		editor_draw_panel_enemy(ed);
	else if (ed->selected.pickable)
		editor_draw_panel_pickable(ed);
	else if (ed->selected.object)
		editor_draw_panel_object(ed);
	else if (ed->selected.sector)
		editor_draw_panel_sector(ed);
	else
		editor_draw_panel_map(ed);
	if (!ed->map_is_updated)
		create_save_button(ed->fonts->amazdoom40,
				ed->panel.surface, &ed->panel, ed);
	draw_on_screen(ed->sdl.surface, ed->panel.surface,
			(t_i_coords){EDIT_W - PANEL_W, 0}, e_true);
}

void	init_panel(t_panel *panel, t_textures *textures)
{
	if (!(panel->surface = SDL_CreateRGBSurface(0, PANEL_W, PANEL_H, 32,
			MASK_RED, MASK_GREEN, MASK_BLUE, MASK_ALPHA)))
	{
		error_doom("Couldn't create Panel Surface");
	}
	create_sub_lists(textures, panel);
	panel->buttons = NULL;
}
