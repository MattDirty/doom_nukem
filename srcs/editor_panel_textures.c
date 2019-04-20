/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_panel_textures.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfatton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/20 06:42:19 by lfatton           #+#    #+#             */
/*   Updated: 2019/04/20 06:42:21 by lfatton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"
#include "editor_panel.h"
#include "editor_draw.h"
#include "editor_panel_buttons.h"
#include "in_which_sector.h"
#include "ui.h"
#include "sounds.h"

void		change_selected_texture(t_params params)
{
	t_btn_params	*btn_params;

	btn_params = (t_btn_params *)params;
	if (!btn_params->selected || *btn_params->selected == btn_params->target)
		return ;
	if (btn_params->ed->selected.pickable)
	{
		if (ft_strstr(btn_params->target->userdata, "shotgun"))
			btn_params->ed->selected.pickable->type = et_shotgun;
		else if (ft_strstr(btn_params->target->userdata, "gun"))
			btn_params->ed->selected.pickable->type = et_gun;
		else if (ft_strstr(btn_params->target->userdata, "vacuum"))
			btn_params->ed->selected.pickable->type = et_vacuum;
	}
	*btn_params->selected = btn_params->target;
	btn_params->ed->map_is_updated = e_false;
}

static void	init_size_and_pos(SDL_Surface *src, t_i_coords *size,
				t_i_coords *pos)
{
	if (src->h > src->w)
	{
		size->x = size->x * src->w / src->h;
		pos->x += (size->y - size->x) / 2;
	}
	else if (src->h < src->w)
	{
		size->y = size->y * src->h / src->w;
		pos->y += (size->x - size->y) / 2;
	}
}

void		draw_miniature(SDL_Surface *dst, SDL_Surface *src, t_i_coords size,
				t_i_coords pos)
{
	t_i_coords	dst_pos;
	t_i_coords	src_pos;
	t_i_coords	step;

	init_size_and_pos(src, &size, &pos);
	dst_pos.y = pos.y;
	step = (t_i_coords){round(src->w / size.x), round(src->h / size.y)};
	src_pos.y = 0;
	while (dst_pos.y < size.y + pos.y && src_pos.y < src->h)
	{
		dst_pos.x = pos.x;
		src_pos.x = 0;
		while (dst_pos.x < size.x + pos.x && src_pos.x < src->w)
		{
			put_pixel(dst, dst_pos.x, dst_pos.y,
					get_pixel(src, src_pos.x, src_pos.y, e_true));
			src_pos.x += step.x;
			dst_pos.x++;
		}
		src_pos.y += step.y;
		dst_pos.y++;
	}
}

void		draw_sprites_section(
				t_editor *ed, t_textures *sprites, char *title, int *y)
{
	SDL_Surface		*s;
	t_texture_node	*node;
	t_i_coords		pos;
	t_button		btn;

	s = write_text(ed->fonts->vcr20, title, (SDL_Colour){255, 255, 255, 255});
	draw_on_screen(ed->panel.surface, s, (t_i_coords){PAN_PAD_L, *y}, e_false);
	SDL_FreeSurface(s);
	node = sprites->first;
	*y += 25;
	pos = (t_i_coords){PAN_PAD_L, *y};
	while (node)
	{
		draw_miniature(ed->panel.surface, node->texture,
				(t_i_coords){PANEL_MINI_W, PANEL_MINI_H}, pos);
		btn.rect = create_rect(pos.x, pos.y, PANEL_MINI_W, PANEL_MINI_H);
		if (ed->selected_sprite && *ed->selected_sprite == node->texture)
			draw_rect(ed->panel.surface, &btn.rect, RED);
		btn.rect.pos.x += PANEL_X;
		btn.f = &change_selected_texture;
		btn.params = create_btn_params(ed->selected_sprite, node->texture, ed);
		add_button_to_list(&ed->panel.buttons, btn);
		pos.x += PANEL_MINI_W + PAN_PAD_L;
		node = node->next;
	}
	*y += 60;
}
