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
#include "editor_panel_buttons.h"
#include "in_which_sector.h"
#include "ui.h"
#include "sounds.h"

void    change_selected_texture(t_params params)
{
    t_btn_params    *btn_params;

    btn_params = (t_btn_params *)params;
    if (!btn_params->selected || *btn_params->selected == btn_params->target)
        return ;
    *btn_params->selected = btn_params->target;
    btn_params->ed->map_is_updated = e_false;
}

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
					get_pixel(src, src_pos.x, src_pos.y, e_true));
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
	t_button		btn;

	title = write_text(ed->fonts->vcr20, title_str,
					   (SDL_Colour){255,255,255,255});
	draw_on_screen(ed->panel.surface, title,
				   (t_i_coords){PANEL_PADDING_LEFT, *y}, e_false);
	SDL_FreeSurface(title);
	node = sprites->first;
	*y += 25;
	pos = (t_i_coords){PANEL_PADDING_LEFT, *y};
	while (node)
	{
		draw_miniature(ed->panel.surface, node->texture,
				(t_i_coords){PANEL_MINIATURE_W, PANEL_MINIATURE_H}, pos);
        btn.rect = create_rect(pos.x, pos.y, PANEL_MINIATURE_W, PANEL_MINIATURE_H);
		if (ed->selected_sprite && *ed->selected_sprite == node->texture)
			draw_rect(ed->panel.surface, &btn.rect, RED);
		btn.rect.pos.x += PANEL_X;
		btn.f = &change_selected_texture;
		btn.params = create_btn_params(ed->selected_sprite, node->texture, ed);
		add_button_to_list(&ed->panel.buttons, btn);
		pos.x += PANEL_MINIATURE_W + PANEL_PADDING_LEFT;
		node = node->next;
	}
    *y += 65;
}

void        draw_panel_back(SDL_Surface *surface)
{
    t_rect  panel;

	panel = create_rect(0, 0, PANEL_W - 1, EDITOR_H - 1);
	draw_rect(surface, &panel, WHITE);
	fill_rect(surface, &panel, PANEL_BACKGROUND, e_false);
}

void        write_panel_state(t_editor *ed, char *state_str)
{
    SDL_Surface *state;

    state = write_text(ed->fonts->vcr40, state_str,
            (SDL_Colour){255,255,255,255});
    draw_on_screen(ed->panel.surface, state,
                   (t_i_coords){PANEL_W / 2 - state->w / 2, 10}, e_false);
    SDL_FreeSurface(state);
}

void save_editor(t_params params)
{
    t_btn_params *ptr;

    ptr = (t_btn_params *)params;
    ptr->ed->map->player_spawn_index = sector_index(
            ptr->ed->map->sectors,
            in_which_sector(ptr->ed->map->spawn, ptr->ed->map->sectors));
    Mix_PlayChannel(-1, ptr->ed->sounds->mip_mep, 0);
    write_file(ptr->ed->map_path, ptr->ed->textures, ptr->ed->map);
    ptr->ed->map_is_updated = e_true;
}

void create_save_button(TTF_Font *font,
                        SDL_Surface *target, t_panel *panel, t_editor *ed)
{
    SDL_Surface *save;
    t_i_coords  pos;
    t_rect      center;
    t_button    save_btn;

    save = write_text(font, "SAVE", (SDL_Colour){255,255,255,255});
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
    if (!ed->map_is_updated)
        create_save_button(ed->fonts->amazdoom40, ed->panel.surface, &ed->panel, ed);
    draw_on_screen(ed->sdl.surface, ed->panel.surface,
				   (t_i_coords){EDITOR_W - PANEL_W, 0}, e_true);
}

void        toggle_lighting(t_params params)
{
    t_btn_params *ptr;

    ptr = (t_btn_params *)params;
    if (!ptr->ed->selected.sector->light)
        ptr->ed->selected.sector->light = 0xDD000000;
    else
        ptr->ed->selected.sector->light = 0;
    ptr->ed->map_is_updated = e_false;
}

void		toggle_skybox(t_params params)
{
	t_btn_params *ptr;

	ptr = (t_btn_params *)params;
	if (!ptr->ed->selected.sector->open_sky)
		ptr->ed->selected.sector->open_sky = e_true;
	else
	{
		ptr->ed->selected.sector->open_sky = e_false;
		ptr->ed->selected.sector->ceil = ptr->ed->selected.sector->floor;
	}
	ptr->ed->map_is_updated = e_false;
}