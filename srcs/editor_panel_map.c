/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_panel_map.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfatton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/20 08:10:00 by lfatton           #+#    #+#             */
/*   Updated: 2019/04/20 08:10:02 by lfatton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"
#include "editor_panel_buttons.h"
#include "editor_mouse_clicks.h"
#include "ui.h"
#include "walls.h"
#include "editor_states.h"

void	create_new_sector_button(t_editor *ed, int *y)
{
	SDL_Surface	*chars;
	t_i_coords	pos;
	t_button	btn;

	chars = write_text(ed->fonts->vcr20, "New Sector",
			(SDL_Colour){0, 0, 0, 0});
	pos.x = PAN_PAD_L + 172;
	pos.y = *y;
	btn.rect = create_rect(pos.x - 12, pos.y - 12, chars->w + 24,
			chars->h + 24);
	fill_rect(ed->panel.surface, &btn.rect, WHITE, e_true);
	draw_on_screen(ed->panel.surface, chars, pos, e_false);
	SDL_FreeSurface(chars);
	btn.rect.pos.x += PANEL_X;
	btn.f = &new_sector_state;
	btn.params = create_btn_params(NULL, NULL, ed);
	add_button_to_list(&ed->panel.buttons, btn);
}

void	editor_draw_panel_map(t_editor *ed)
{
	int	y;

	write_panel_state(ed, "MAP");
	y = 60;
	ed->selected_sprite = &ed->map->daysky;
	draw_sprites_section(ed, ed->panel.skies.first, "Skybox Day:", &y);
	y += 20;
	ed->selected_sprite = &ed->map->nightsky;
	draw_sprites_section(ed, ed->panel.skies.first, "Skybox Night:", &y);
	y += 100;
	add_enemy_btn(ed, ed->fonts->vcr40, ed->panel.surface, &y);
	y += 70;
	add_object_btn(ed, ed->fonts->vcr40, ed->panel.surface, &y);
	y += 70;
	add_weapon_btn(ed, ed->fonts->vcr40, ed->panel.surface, &y);
}

void	create_save_button(TTF_Font *font,
			SDL_Surface *target, t_panel *panel, t_editor *ed)
{
	SDL_Surface	*save;
	t_i_coords	pos;
	t_rect		center;
	t_button	save_btn;

	save = write_text(font, "SAVE", (SDL_Colour){255, 255, 255, 255});
	pos.x = PANEL_W - save->w - 100;
	pos.y = PANEL_H - save->h - 30;
	save_btn.rect = create_rect(
			pos.x - 12, pos.y - 12, save->w + 24, save->h + 8);
	center = create_rect(pos.x - 8, pos.y - 8, save->w + 16, save->h + 0);
	fill_rect(target, &save_btn.rect, SAVE_BORDER, e_false);
	fill_rect(target, &center, SAVE_CENTER, e_false);
	draw_on_screen(target, save, pos, e_false);
	save_btn.rect.pos.x += PANEL_X;
	save_btn.f = &save_editor;
	save_btn.params = create_btn_params(NULL, NULL, ed);
	add_button_to_list(&panel->buttons, save_btn);
	SDL_FreeSurface(save);
}
