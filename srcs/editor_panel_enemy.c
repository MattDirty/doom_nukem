/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_panel_enemy.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfatton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/20 07:56:01 by lfatton           #+#    #+#             */
/*   Updated: 2019/04/20 07:56:03 by lfatton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"
#include "editor_panel_buttons.h"
#include "editor_mouse_clicks.h"
#include "ui.h"
#include "walls.h"
#include "editor_states.h"

void	remove_selected_enemy(t_editor *ed)
{
	t_sector	*sector;

	sector = find_enemy_sector(ed->map->sectors, ed->selected.enemy);
	delete_enemy(&sector->enemies, ed->selected.enemy);
	clear_selection(&ed->selected);
	ed->map_is_updated = e_false;
}

void	hp_btn(t_editor *ed, TTF_Font *font, SDL_Surface *target, int *y)
{
	SDL_Surface	*chars;
	t_i_coords	pos;
	t_button	btn;
	char		*str;

	str = ft_strjoinfree("HP : ",
			ft_itoa(ed->selected.enemy->life_remaining), 2);
	chars = write_text(font, str, (SDL_Colour){255, 255, 255, 255});
	free(str);
	pos.x = PAN_PAD_L + 8;
	pos.y = *y - 35;
	btn.rect = create_rect(pos.x - 6, pos.y - 6, chars->w + 10, chars->h);
	draw_rect(target, &btn.rect, BLACK);
	fill_rect(target, &btn.rect, RED, e_true);
	draw_on_screen(target, chars, pos, e_false);
	btn.rect.pos.x += PANEL_X;
	btn.f = &change_enemy_hp;
	btn.params = create_btn_params(NULL, NULL, ed);
	add_button_to_list(&ed->panel.buttons, btn);
	SDL_FreeSurface(chars);
}

void	change_enemy_hp(t_params params)
{
	t_enemy	*enemy;

	enemy = ((t_btn_params *)params)->ed->selected.enemy;
	enemy->life_remaining += ((t_btn_params *)params)->ed->multi_purpose_int;
	if (enemy->life_remaining < 5)
		enemy->life_remaining = 5;
	else
		((t_btn_params *)params)->ed->map_is_updated = e_false;
}

void	add_enemy_btn(t_editor *ed, TTF_Font *font, SDL_Surface *target, int *y)
{
	SDL_Surface	*add_enemy;
	t_i_coords	pos;
	t_button	enemy_btn;

	add_enemy = write_text(font, "Add enemy ", (SDL_Colour){255, 0, 0, 255});
	pos.x = PAN_PAD_L + 8;
	pos.y = *y - 35;
	enemy_btn.rect = create_rect(pos.x - 6, pos.y - 6,
			add_enemy->w + 10, add_enemy->h + 10);
	draw_rect(target, &enemy_btn.rect, BLACK);
	fill_rect(target, &enemy_btn.rect, ENEMY_COLOR, e_true);
	draw_on_screen(target, add_enemy, pos, e_false);
	enemy_btn.rect.pos.x += PANEL_X;
	enemy_btn.f = &create_enemy_in_map_state;
	enemy_btn.params = create_btn_params(NULL, NULL, ed);
	add_button_to_list(&ed->panel.buttons, enemy_btn);
	SDL_FreeSurface(add_enemy);
}

void	editor_draw_panel_enemy(t_editor *ed)
{
	int	y;

	write_panel_state(ed, "Baddy");
	y = 120;
	if (ed->selected.enemy->type != et_boss)
		remove_btn(ed, ed->fonts->vcr20, ed->panel.surface, &y);
	y += 70;
	hp_btn(ed, ed->fonts->amazdoom40, ed->panel.surface, &y);
	y += 70;
	width_btn(ed, ed->fonts->vcr20, ed->panel.surface, &y);
	y += 50;
	height_btn(ed, ed->fonts->vcr20, ed->panel.surface, &y);
	y += 50;
	z_btn(ed, ed->fonts->vcr20, ed->panel.surface, &y);
}
