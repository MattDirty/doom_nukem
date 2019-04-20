/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_panel_sector.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfatton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/20 08:07:30 by lfatton           #+#    #+#             */
/*   Updated: 2019/04/20 08:07:31 by lfatton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"
#include "editor_panel_buttons.h"
#include "editor_mouse_clicks.h"
#include "ui.h"
#include "walls.h"
#include "editor_states.h"

void	toggle_skybox(t_params params)
{
	t_btn_params	*ptr;

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

void	toggle_lighting(t_params params)
{
	t_btn_params	*ptr;

	ptr = (t_btn_params *)params;
	if (!ptr->ed->selected.sector->light)
		ptr->ed->selected.sector->light = 0xDD000000;
	else
		ptr->ed->selected.sector->light = 0;
	ptr->ed->map_is_updated = e_false;
}

void	create_light_btn(TTF_Font *font,
			SDL_Surface *target, Uint32 light_color, t_editor *ed)
{
	SDL_Surface	*light;
	t_i_coords	pos;
	t_button	light_btn;

	if (!ed->selected.sector->light)
		light = write_text(font, "Lights off", (SDL_Colour){0, 0, 0, 255});
	else
		light = write_text(font, "Lights on ",
				(SDL_Colour){255, 255, 255, 255});
	pos.x = PAN_PAD_L + 10;
	pos.y = PANEL_H - light->h - 50;
	light_btn.rect = create_rect(pos.x - 6, pos.y - 6, light->w + 10,
			light->h + 10);
	draw_rect(target, &light_btn.rect, YELLOW);
	fill_rect(target, &light_btn.rect, WHITE, e_false);
	fill_rect(target, &light_btn.rect, light_color, e_true);
	draw_on_screen(target, light, pos, e_false);
	light_btn.rect.pos.x += PANEL_X;
	light_btn.f = &toggle_lighting;
	light_btn.params = create_btn_params(NULL, NULL, ed);
	add_button_to_list(&ed->panel.buttons, light_btn);
	SDL_FreeSurface(light);
}

void	create_sky_toggle_btn(TTF_Font *font,
			SDL_Surface *target, t_editor *ed, int *y)
{
	SDL_Surface	*tgl;
	t_i_coords	pos;
	t_button	sky_btn;
	Uint32		sky_color;
	Uint32		outer_color;

	tgl = write_text(font, "Ceiling ", (SDL_Colour){0, 0, 0, 255});
	sky_color = SKY_OFF;
	outer_color = BLACK;
	if (ed->selected.sector->open_sky && (sky_color = SKY_ON))
	{
		tgl = write_text(font, "Open sky", (SDL_Colour){0, 0, 0, 255});
		outer_color = RED;
	}
	pos.x = PAN_PAD_L + 205;
	pos.y = *y - 35;
	sky_btn.rect = create_rect(pos.x - 6, pos.y - 6, tgl->w + 10, tgl->h + 10);
	draw_rect(target, &sky_btn.rect, outer_color);
	fill_rect(target, &sky_btn.rect, sky_color, e_true);
	draw_on_screen(target, tgl, pos, e_false);
	sky_btn.rect.pos.x += PANEL_X;
	sky_btn.f = &toggle_skybox;
	sky_btn.params = create_btn_params(NULL, NULL, ed);
	add_button_to_list(&ed->panel.buttons, sky_btn);
	SDL_FreeSurface(tgl);
}

void	editor_draw_panel_sector(t_editor *ed)
{
	int y;

	write_panel_state(ed, "SECTOR");
	y = 60;
	ed->selected_sprite = &ed->selected.sector->floor;
	draw_sprites_section(ed, &ed->panel.walls, "Floor:", &y);
	draw_sprites_section(ed, &ed->panel.flats, " ", &y);
	y += 20;
	if (!(ed->selected.sector->open_sky))
		ed->selected_sprite = &ed->selected.sector->ceil;
	else
		ed->selected_sprite = NULL;
	draw_sprites_section(ed, &ed->panel.walls, "Ceiling:", &y);
	draw_sprites_section(ed, &ed->panel.flats, " ", &y);
	create_light_btn(ed->fonts->vcr40, ed->panel.surface,
			ed->selected.sector->light, ed);
	create_sky_toggle_btn(ed->fonts->vcr20, ed->panel.surface, ed, &y);
}
