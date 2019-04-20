/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_panel_object.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfatton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/20 07:53:37 by lfatton           #+#    #+#             */
/*   Updated: 2019/04/20 07:53:39 by lfatton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"
#include "editor_panel_buttons.h"
#include "editor_mouse_clicks.h"
#include "ui.h"
#include "walls.h"
#include "editor_states.h"

void	change_object_width(t_params params)
{
	double		*target;
	t_editor	*ed;

	ed = ((t_btn_params *)params)->ed;
	if (ed->selected.enemy)
		target = &ed->selected.enemy->object->horizontal_size;
	else
		target = &ed->selected.object->horizontal_size;
	*target += (ed->multi_purpose_int / 100.0);
	if (*target < 0.05)
		*target = 0.05;
	else if (*target > 1)
		*target = 1;
	else
		ed->map_is_updated = e_false;
}

void	change_object_z(t_params params)
{
	double		*target;
	t_editor	*ed;

	ed = ((t_btn_params *)params)->ed;
	if (ed->selected.enemy)
		target = &ed->selected.enemy->object->z;
	else
		target = &ed->selected.object->z;
	*target += (ed->multi_purpose_int / 100.0);
	if (*target < 0)
		*target = 0;
	else if (*target > 0.95)
		*target = 0.95;
	else
		ed->map_is_updated = e_false;
}

void	change_object_height(t_params params)
{
	double		*target;
	t_editor	*ed;

	ed = ((t_btn_params *)params)->ed;
	if (ed->selected.enemy)
		target = &ed->selected.enemy->object->vertical_size;
	else
		target = &ed->selected.object->vertical_size;
	*target += (ed->multi_purpose_int / 100.0);
	if (*target < 0.05)
		*target = 0.05;
	else if (*target > 1)
		*target = 1;
	else
		ed->map_is_updated = e_false;
}

void	add_object_btn(t_editor *ed, TTF_Font *font, SDL_Surface *target,
			int *y)
{
	SDL_Surface	*add_object;
	t_i_coords	pos;
	t_button	object_btn;

	add_object = write_text(font, "Add object", (SDL_Colour){255, 0, 0, 255});
	pos.x = PAN_PAD_L + 8;
	pos.y = *y - 35;
	object_btn.rect = create_rect(pos.x - 6, pos.y - 6, add_object->w + 10,
			add_object->h + 10);
	draw_rect(target, &object_btn.rect, BLACK);
	fill_rect(target, &object_btn.rect, OBJECT_COLOR, e_true);
	draw_on_screen(target, add_object, pos, e_false);
	object_btn.rect.pos.x += PANEL_X;
	object_btn.f = &create_object_in_map_state;
	object_btn.params = create_btn_params(NULL, NULL, ed);
	add_button_to_list(&ed->panel.buttons, object_btn);
	SDL_FreeSurface(add_object);
}

void	editor_draw_panel_object(t_editor *ed)
{
	int	y;

	write_panel_state(ed, "Flower");
	y = 120;
	remove_btn(ed, ed->fonts->vcr20, ed->panel.surface, &y);
	y += 50;
	width_btn(ed, ed->fonts->vcr20, ed->panel.surface, &y);
	y += 50;
	height_btn(ed, ed->fonts->vcr20, ed->panel.surface, &y);
	y += 50;
	z_btn(ed, ed->fonts->vcr20, ed->panel.surface, &y);
}
