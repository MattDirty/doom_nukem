/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_panel.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfatton <lfatton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 02:45:22 by lfatton           #+#    #+#             */
/*   Updated: 2019/04/12 02:45:24 by lfatton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"
#include "editor_panel.h"
#include "editor_draw.h"
#include "ui.h"

void	draw_miniature(
		SDL_Surface *dst, SDL_Surface *src, t_i_coords size, t_i_coords pos)
{
	t_i_coords	dst_pos;
	t_i_coords	src_pos;
	t_i_coords	step;

	if (src->h > src->w)
	{
		size.x = size.x * src->w / src->h;
		pos.x += (size.y - size.x) / 2;
	}
	else if (src->h < src->w)
	{
		size.y = size.y * src->h / src->w;
		pos.y += (size.x - size.y) / 2;
	}
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
					get_pixel(src, src_pos.x, src_pos.y, t_true));
			src_pos.x += step.x;
			dst_pos.x++;
		}
		src_pos.y += step.y;
		dst_pos.y++;
	}
}

void		draw_sprites_section(
		t_editor *ed, t_textures *sprites, char *title_str, int *y)
{
	SDL_Surface		*title;
	t_texture_node	*node;
	t_i_coords		pos;
	t_rect			rect;

	title = write_text(ed->fonts->vcr20, title_str,
					   (SDL_Colour){255,255,255,255});
	draw_on_screen(ed->panel.surface, title,
				   (t_i_coords){PANEL_PADDING_LEFT, *y}, t_false);
	SDL_FreeSurface(title);
	node = sprites->first;
	*y += 25;
	pos = (t_i_coords){PANEL_PADDING_LEFT, *y};
	while (node)
	{
		draw_miniature(ed->panel.surface, node->texture,
				(t_i_coords){PANEL_MINIATURE_MAX_W, PANEL_MINIATURE_MAX_H},
				pos);
		if (ed->selected_sprite_str
		    && ft_strcmp(ed->selected_sprite_str, node->texture->userdata) == 0)
		{
			rect = create_rect(pos.x, pos.y, PANEL_MINIATURE_MAX_W,
					PANEL_MINIATURE_MAX_H);
			draw_rect(ed->panel.surface, &rect, RED);
		}
		pos.x += PANEL_MINIATURE_MAX_W + PANEL_PADDING_LEFT;
		node = node->next;
	}
	*y += 65;
}

void        draw_panel_back(SDL_Surface *surface)
{
    t_rect  panel;

	panel = create_rect(0, 0, PANEL_W - 1, EDITOR_H - 1);
	draw_rect(surface, &panel, WHITE);
	fill_rect(surface, &panel, PANEL_BACKGROUND);
}

void        write_panel_state(t_editor *ed, char *state_str)
{
    SDL_Surface *state;

    state = write_text(ed->fonts->vcr40, state_str,
            (SDL_Colour){255,255,255,255});
    draw_on_screen(ed->panel.surface, state,
                   (t_i_coords){PANEL_W / 2 - state->w / 2, 10}, t_false);
    SDL_FreeSurface(state);
}

void        draw_panel(t_editor *ed)
{
    draw_panel_back(ed->panel.surface);
    if (ed->selected.wall)
        editor_draw_panel_walls(ed);
    else if (ed->selected.object || ed->selected.enemy)
        editor_draw_panel_sprites(ed);
    else if (ed->selected.sector)
        editor_draw_panel_sector(ed);
    else
        editor_draw_panel_map(ed);
	draw_on_screen(ed->sdl.surface, ed->panel.surface,
				   (t_i_coords){EDITOR_W - PANEL_W, 0}, t_true);
}