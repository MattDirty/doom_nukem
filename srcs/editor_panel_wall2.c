/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_panel_wall2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfatton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/20 08:02:37 by lfatton           #+#    #+#             */
/*   Updated: 2019/04/20 08:02:38 by lfatton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"
#include "editor_panel_buttons.h"
#include "editor_mouse_clicks.h"
#include "ui.h"
#include "walls.h"
#include "editor_states.h"

void	change_window_in_wall_button(t_editor *ed, int *y)
{
	SDL_Surface	*chars;
	t_i_coords	pos;
	t_button	btn;

	chars = write_text(ed->fonts->vcr20, "Transform in wall",
			(SDL_Colour){255, 0, 0, 0});
	pos.x = PAN_PAD_L + 12;
	pos.y = *y;
	btn.rect = create_rect(pos.x - 12, pos.y - 12, chars->w + 24,
			chars->h + 24);
	fill_rect(ed->panel.surface, &btn.rect, WHITE, e_true);
	draw_on_screen(ed->panel.surface, chars, pos, e_false);
	SDL_FreeSurface(chars);
	btn.rect.pos.x += PANEL_X;
	btn.f = &change_wall_in_window;
	btn.params = create_btn_params(NULL, NULL, ed);
	add_button_to_list(&ed->panel.buttons, btn);
}

void	change_wall_in_window_button(t_editor *ed, int *y)
{
	SDL_Surface	*chars;
	t_i_coords	pos;
	t_button	btn;

	chars = write_text(ed->fonts->vcr20, "Transform in window",
			(SDL_Colour){0, 0, 255, 0});
	pos.x = PAN_PAD_L + 12;
	pos.y = *y;
	btn.rect = create_rect(pos.x - 12, pos.y - 12, chars->w + 24,
			chars->h + 24);
	fill_rect(ed->panel.surface, &btn.rect, WHITE, e_true);
	draw_on_screen(ed->panel.surface, chars, pos, e_false);
	SDL_FreeSurface(chars);
	btn.rect.pos.x += PANEL_X;
	btn.f = &change_wall_in_window;
	btn.params = create_btn_params(NULL, NULL, ed);
	add_button_to_list(&ed->panel.buttons, btn);
}

void	create_transform_portal_to_door_button(t_editor *ed, int *y)
{
	SDL_Surface	*chars;
	t_i_coords	pos;
	t_button	btn;

	chars = write_text(ed->fonts->vcr20, "Transform in door",
			(SDL_Colour){0, 0, 255, 0});
	pos.x = PAN_PAD_L + 12;
	pos.y = *y;
	btn.rect = create_rect(pos.x - 12, pos.y - 12, chars->w + 24,
			chars->h + 24);
	fill_rect(ed->panel.surface, &btn.rect, WHITE, e_true);
	draw_on_screen(ed->panel.surface, chars, pos, e_false);
	SDL_FreeSurface(chars);
	btn.rect.pos.x += PANEL_X;
	btn.f = &change_portal_to_door;
	btn.params = create_btn_params(NULL, NULL, ed);
	add_button_to_list(&ed->panel.buttons, btn);
}

void	create_transform_door_to_portal_button(t_editor *ed, int *y)
{
	SDL_Surface	*chars;
	t_i_coords	pos;
	t_button	btn;

	chars = write_text(ed->fonts->vcr20, "Transform in portal",
			(SDL_Colour){255, 0, 0, 0});
	pos.x = PAN_PAD_L + 12;
	pos.y = *y;
	btn.rect = create_rect(pos.x - 12, pos.y - 12, chars->w + 24,
			chars->h + 24);
	fill_rect(ed->panel.surface, &btn.rect, WHITE, e_true);
	draw_on_screen(ed->panel.surface, chars, pos, e_false);
	SDL_FreeSurface(chars);
	btn.rect.pos.x += PANEL_X;
	btn.f = &change_door_to_portal;
	btn.params = create_btn_params(NULL, NULL, ed);
	add_button_to_list(&ed->panel.buttons, btn);
}
