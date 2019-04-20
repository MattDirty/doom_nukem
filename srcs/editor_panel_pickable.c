/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_panel_pickable.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfatton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/20 08:03:44 by lfatton           #+#    #+#             */
/*   Updated: 2019/04/20 08:03:46 by lfatton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"
#include "editor_panel_buttons.h"
#include "editor_mouse_clicks.h"
#include "ui.h"
#include "walls.h"
#include "editor_states.h"

void	remove_selected_pickable(t_editor *ed)
{
	t_sector	*sector;

	sector = find_pickable_sector(ed->map->sectors, ed->selected.pickable);
	delete_pickable(&sector->pickables, ed->selected.pickable);
	clear_selection(&ed->selected);
	ed->map_is_updated = e_false;
}

void	add_weapon_btn(t_editor *ed, TTF_Font *font, SDL_Surface *target,
			int *y)
{
	SDL_Surface	*add_weapon;
	t_i_coords	pos;
	t_button	weapon_btn;

	add_weapon = write_text(font, "Add weapon", (SDL_Colour){255, 0, 0, 255});
	pos.x = PAN_PAD_L + 8;
	pos.y = *y - 35;
	weapon_btn.rect = create_rect(pos.x - 6, pos.y - 6, add_weapon->w + 10,
			add_weapon->h + 10);
	draw_rect(target, &weapon_btn.rect, BLACK);
	fill_rect(target, &weapon_btn.rect, PICKABLE_COLOR, e_true);
	draw_on_screen(target, add_weapon, pos, e_false);
	weapon_btn.rect.pos.x += PANEL_X;
	weapon_btn.f = &create_pickable_in_map_state;
	weapon_btn.params = create_btn_params(NULL, NULL, ed);
	add_button_to_list(&ed->panel.buttons, weapon_btn);
	SDL_FreeSurface(add_weapon);
}

void	editor_draw_panel_pickable(t_editor *ed)
{
	int y;

	write_panel_state(ed, "Weapon");
	y = 120;
	remove_btn(ed, ed->fonts->vcr20, ed->panel.surface, &y);
	ed->selected_sprite = &ed->selected.pickable->object->sprite;
	draw_sprites_section(ed, &ed->panel.pickables, " ", &y);
}
