/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_loop.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfatton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/20 05:17:16 by lfatton           #+#    #+#             */
/*   Updated: 2019/04/20 05:17:18 by lfatton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"
#include "editor_move_stuff.h"

static void	rand_lighting(t_editor *ed, t_sector *sector)
{
	Uint8	a;
	Uint8	r;
	Uint8	g;
	Uint8	b;

	a = rand() % 100;
	r = rand() % 255;
	g = rand() % 255;
	b = rand() % 255;
	if (!a)
		a = 1;
	sector->light = (a << 24) + (r << 16) + (g << 8) + b;
	ed->map_is_updated = e_false;
}

void		event_editor(t_editor *ed)
{
	double		x;
	double		y;
	SDL_Event	ev;
	int			mouse_x;
	int			mouse_y;

	x = 0;
	y = 0;
	while (SDL_PollEvent(&ev))
	{
		if (ev.type == SDL_MOUSEMOTION)
		{
			x += ev.motion.xrel;
			y += ev.motion.yrel;
		}
		if (ev.key.keysym.scancode == SDL_SCANCODE_ESCAPE
			|| ev.type == SDL_QUIT)
			quit_editor(ed);
		if (ev.type == SDL_MOUSEBUTTONDOWN)
		{
			if (ev.button.button == SDL_BUTTON_LEFT)
				ed->multi_purpose_int = 5;
			else if (ev.button.button == SDL_BUTTON_RIGHT)
				ed->multi_purpose_int = -5;
			mousedown_action(ed, ev.button.x, ev.button.y);
		}
		if (ev.type == SDL_MOUSEBUTTONUP)
			mouseup_action(ed, ev.button.x, ev.button.y);
		if (ev.type == SDL_MOUSEWHEEL)
		{
			ed->zoom += ev.wheel.y;
			if (ed->zoom <= 1)
				ed->zoom = 1;
		}
		if (ev.type == SDL_KEYDOWN)
		{
			move_map(ed, ev.key.keysym.scancode);
			if (ed->selected.sector && ed->selected.sector->light
				&& ev.key.keysym.scancode == SDL_SCANCODE_R)
				rand_lighting(ed, ed->selected.sector);
		}
	}
	if (x || y)
	{
		SDL_GetMouseState(&mouse_x, &mouse_y);
		if (ed->dragged.nodes)
			move_walls_nodes(ed, mouse_x, mouse_y);
		else if (ed->dragged.p_spawn)
			move_player_spawn(ed, mouse_x, mouse_y);
		else if (ed->dragged.enemy)
			move_enemy(ed, mouse_x, mouse_y);
		else if (ed->dragged.pickable)
			move_pickable(ed, mouse_x, mouse_y);
		else if (ed->dragged.object)
			move_object(ed, mouse_x, mouse_y);
	}
}

void		reframe_editor(t_editor *ed)
{
	SDL_Texture *texture;

	draw_background(ed);
	draw_editor(ed);
	draw_panel(ed);
	SDL_RenderClear(ed->sdl.renderer);
	if (!(texture = SDL_CreateTextureFromSurface(ed->sdl.renderer,
					ed->sdl.surface)))
		error_doom("Could not create texture");
	SDL_RenderCopy(ed->sdl.renderer, texture, 0, 0);
	SDL_RenderPresent(ed->sdl.renderer);
	SDL_DestroyTexture(texture);
}

void		editor_loop(t_editor *ed)
{
	reframe_editor(ed);
	create_linked_walls_from_sectors(
			ed->map->sectors, &ed->linked_walls, &ed->linked_walls_count);
	while (1)
	{
		reframe_editor(ed);
		event_editor(ed);
	}
}
