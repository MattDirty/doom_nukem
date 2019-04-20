/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_panel_object2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfatton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/20 08:05:45 by lfatton           #+#    #+#             */
/*   Updated: 2019/04/20 08:05:48 by lfatton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"
#include "editor_panel_buttons.h"
#include "editor_mouse_clicks.h"
#include "ui.h"
#include "walls.h"
#include "editor_states.h"

void	remove_selected_object(t_params params)
{
	t_object	*object;
	t_sector	*sector;
	t_editor	*ed;

	ed = ((t_btn_params *)params)->ed;
	if (ed->selected.enemy && ed->selected.enemy->type)
	{
		remove_selected_enemy(ed);
		return ;
	}
	if (ed->selected.pickable)
	{
		remove_selected_pickable(ed);
		return ;
	}
	object = ed->selected.object;
	sector = find_object_sector(ed->map->sectors, object);
	remove_object(object, sector->objects);
	clear_selection(&ed->selected);
	ed->map_is_updated = e_false;
}

void	width_btn(t_editor *ed, TTF_Font *font, SDL_Surface *target, int *y)
{
	SDL_Surface	*chars;
	t_i_coords	pos;
	t_button	btn;
	char		*str;

	if (ed->selected.enemy)
		str = ft_strjoinfree("Width : ", ft_itoa(
				round(ed->selected.enemy->object->horizontal_size * 100)), 2);
	else
		str = ft_strjoinfree("Width : ", ft_itoa(
				round(ed->selected.object->horizontal_size * 100)), 2);
	chars = write_text(font, str, (SDL_Colour){255, 255, 255, 255});
	free(str);
	pos.x = PAN_PAD_L + 8;
	pos.y = *y - 35;
	btn.rect = create_rect(pos.x - 6, pos.y - 6, chars->w + 12, chars->h + 12);
	draw_rect(target, &btn.rect, BLACK);
	fill_rect(target, &btn.rect, 0xFF00AA00, e_true);
	draw_on_screen(target, chars, pos, e_false);
	btn.rect.pos.x += PANEL_X;
	btn.f = &change_object_width;
	btn.params = create_btn_params(NULL, NULL, ed);
	add_button_to_list(&ed->panel.buttons, btn);
	SDL_FreeSurface(chars);
}

void	height_btn(t_editor *ed, TTF_Font *font, SDL_Surface *target, int *y)
{
	SDL_Surface	*chars;
	t_i_coords	pos;
	t_button	btn;
	char		*str;

	if (ed->selected.enemy)
		str = ft_strjoinfree("Height : ", ft_itoa(round(
				ed->selected.enemy->object->vertical_size * 100)), 2);
	else
		str = ft_strjoinfree("Height : ", ft_itoa(
				round(ed->selected.object->vertical_size * 100)), 2);
	chars = write_text(font, str, (SDL_Colour){255, 255, 255, 255});
	free(str);
	pos.x = PAN_PAD_L + 8;
	pos.y = *y - 35;
	btn.rect = create_rect(pos.x - 6, pos.y - 6, chars->w + 12, chars->h + 12);
	draw_rect(target, &btn.rect, BLACK);
	fill_rect(target, &btn.rect, 0xFF00AA00, e_true);
	draw_on_screen(target, chars, pos, e_false);
	btn.rect.pos.x += PANEL_X;
	btn.f = &change_object_height;
	btn.params = create_btn_params(NULL, NULL, ed);
	add_button_to_list(&ed->panel.buttons, btn);
	SDL_FreeSurface(chars);
}

void	z_btn(t_editor *ed, TTF_Font *font, SDL_Surface *target, int *y)
{
	SDL_Surface	*chars;
	t_i_coords	pos;
	t_button	btn;
	char		*str;

	if (ed->selected.enemy)
		str = ft_strjoinfree("Z axis : ", ft_itoa(
				round(ed->selected.enemy->object->z * 100)), 2);
	else
		str = ft_strjoinfree("Z axis : ", ft_itoa(
				round(ed->selected.object->z * 100)), 2);
	chars = write_text(font, str, (SDL_Colour){255, 255, 255, 255});
	free(str);
	pos.x = PAN_PAD_L + 8;
	pos.y = *y - 35;
	btn.rect = create_rect(pos.x - 6, pos.y - 6, chars->w + 12, chars->h + 12);
	draw_rect(target, &btn.rect, BLACK);
	fill_rect(target, &btn.rect, 0xFF00AA00, e_true);
	draw_on_screen(target, chars, pos, e_false);
	btn.rect.pos.x += PANEL_X;
	btn.f = &change_object_z;
	btn.params = create_btn_params(NULL, NULL, ed);
	add_button_to_list(&ed->panel.buttons, btn);
	SDL_FreeSurface(chars);
}

void	remove_btn(t_editor *ed, TTF_Font *font, SDL_Surface *target, int *y)
{
	SDL_Surface	*add_enemy;
	t_i_coords	pos;
	t_button	enemy_btn;

	add_enemy = write_text(font, "Remove", (SDL_Colour){255, 0, 0, 255});
	pos.x = PAN_PAD_L + 8;
	pos.y = *y - 35;
	enemy_btn.rect = create_rect(pos.x - 6, pos.y - 6, add_enemy->w + 10,
			add_enemy->h + 10);
	draw_rect(target, &enemy_btn.rect, BLACK);
	fill_rect(target, &enemy_btn.rect, ENEMY_COLOR, e_true);
	draw_on_screen(target, add_enemy, pos, e_false);
	enemy_btn.rect.pos.x += PANEL_X;
	enemy_btn.f = &remove_selected_object;
	enemy_btn.params = create_btn_params(NULL, NULL, ed);
	add_button_to_list(&ed->panel.buttons, enemy_btn);
	SDL_FreeSurface(add_enemy);
}
