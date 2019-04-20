/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_draw.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badhont <badhont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 19:50:23 by badhont           #+#    #+#             */
/*   Updated: 2019/04/20 15:44:34 by badhont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "default.h"
#include "editor.h"
#include "map.h"
#include "utils.h"
#include "struct_sdl.h"
#include "ui.h"
#include "utils.h"
#include "editor_checks.h"
#include "editor_draw.h"

void	draw_background(t_editor *ed)
{
	t_rect background;

	background = create_rect(-1, -1, EDIT_W + 1, EDIT_H + 1);
	fill_rect(ed->sdl.surface, &background, BACKGROUND_COLOR, e_false);
}

void	draw_player_spawn(SDL_Surface *surface, t_coords spawn,
			t_i_coords map_offset, int zoom)
{
	t_coords	coords;
	
	coords.x = map_offset.x + spawn.x * zoom;
	coords.y = map_offset.y - spawn.y * zoom;
	draw_circle_filled(surface, coords, 6, PLAYER_COLOR);
}

void	show_possible_new_sector(t_editor *ed, int x, int y)
{
	t_segment	s1;
	t_segment	s2;
	t_segment	s3;
	Uint32		color;

	s3 = ed->selected.wall->segment;
	s1.x1 = ed->map_offset.x + s3.x1 * ed->zoom;
	s1.y1 = ed->map_offset.y - s3.y1 * ed->zoom;
	s1.x2 = x;
	s1.y2 = y;
	s2.x2 = ed->map_offset.x + s3.x2 * ed->zoom;
	s2.y2 = ed->map_offset.y - s3.y2 * ed->zoom;
	s2.x1 = x;
	s2.y1 = y;
	if (!new_node_pos_valid(ed, (t_coords){
				(double)(x - ed->map_offset.x) / ed->zoom,
				(double)(ed->map_offset.y - y) / ed->zoom}))
		color = 0x969696FF;
	else
		color = 0x96FF0000;
	draw_segment(ed->sdl.surface, s1, color);
	draw_segment(ed->sdl.surface, s2, color);
}

void	draw_editor(t_editor *ed)
{
	int	i;
	int	mouse_x;
	int	mouse_y;

	i = -1;
	while (++i < ed->map->sectors->count)
	{
		draw_walls_editor(ed->sdl.surface, ed->map->sectors->items[i]->walls,
				ed->map_offset, ed->zoom);
		draw_objects_in_sector_editor(ed->sdl.surface,
				ed->map->sectors->items[i]->objects, ed->map_offset, ed->zoom);
		draw_enemies_in_sector_editor(ed->sdl.surface,
				ed->map->sectors->items[i]->enemies, ed->map_offset, ed->zoom);
		draw_pickables_in_sector_editor(ed->sdl.surface,
				ed->map->sectors->items[i]->pickables, ed->map_offset,
				ed->zoom);
	}
	draw_player_spawn(ed->sdl.surface, ed->map->spawn, ed->map_offset,
			ed->zoom);
	SDL_GetMouseState(&mouse_x, &mouse_y);
	if (mouse_x < PANEL_X)
	{
		if (ed->state == e_add_sector)
			show_possible_new_sector(ed, mouse_x, mouse_y);
	}
}
