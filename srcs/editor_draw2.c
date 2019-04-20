/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_draw2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfatton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/20 04:36:24 by lfatton           #+#    #+#             */
/*   Updated: 2019/04/20 04:36:26 by lfatton          ###   ########.fr       */
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

void	draw_corners_editor(SDL_Surface *surface, t_segment *s)
{
	t_rect	rect;

	rect.width = CORNER_SIZE;
	rect.height = CORNER_SIZE;
	rect.pos.x = s->x1 - CORNER_SIZE / 2;
	rect.pos.y = s->y1 - CORNER_SIZE / 2;
	draw_rect(surface, &rect, L_BLUE);
	fill_rect(surface, &rect, L_BLUE, e_false);
	rect.pos.x = s->x2 - CORNER_SIZE / 2;
	rect.pos.y = s->y2 - CORNER_SIZE / 2;
	draw_rect(surface, &rect, L_BLUE);
	fill_rect(surface, &rect, L_BLUE, e_false);
}

void	draw_walls_editor(SDL_Surface *surface, t_walls *walls,
		t_i_coords map_offset, int zoom)
{
	int			i;
	t_segment	s;

	i = 0;
	while (i < walls->count)
	{
		s = walls->items[i]->segment;
		s.x1 = map_offset.x + s.x1 * zoom;
		s.y1 = map_offset.y - s.y1 * zoom;
		s.x2 = map_offset.x + s.x2 * zoom;
		s.y2 = map_offset.y - s.y2 * zoom;
		if (walls->items[i]->type == e_portal)
			draw_segment(surface, s, RED);
		else if (walls->items[i]->type == e_wall)
			draw_segment(surface, s, WHITE);
		else if (walls->items[i]->type == e_transparent_wall)
			draw_segment(surface, s, BLUE);
		draw_corners_editor(surface, &s);
		i++;
	}
}

void	draw_enemies_in_sector_editor(SDL_Surface *target,
			t_linked_enemies *enemies, t_i_coords map_offset, int zoom)
{
	t_coords	coords;

	while (enemies)
	{
		coords.x = map_offset.x + enemies->item.object->x * zoom;
		coords.y = map_offset.y - enemies->item.object->y * zoom;
		if (enemies->item.type != et_boss)
			draw_circle_filled(target, coords, 5, ENEMY_COLOR);
		else
			draw_circle_filled(target, coords, 8, 0);
		enemies = enemies->next;
	}
}

void	draw_objects_in_sector_editor(SDL_Surface *target, t_objects *objects,
			t_i_coords map_offset, int zoom)
{
	int			i;
	t_coords	coords;

	i = 0;
	while (i < objects->count)
	{
		coords.x = map_offset.x + objects->items[i].x * zoom;
		coords.y = map_offset.y - objects->items[i].y * zoom;
		draw_circle_filled(target, coords, 3, OBJECT_COLOR);
		i++;
	}
}

void	draw_pickables_in_sector_editor(SDL_Surface *target,
			t_pickables *pickables, t_i_coords map_offset, int zoom)
{
	t_coords	coords;

	while (pickables)
	{
		coords.x = map_offset.x + pickables->item.object->x * zoom;
		coords.y = map_offset.y - pickables->item.object->y * zoom;
		draw_circle_filled(target, coords, 4, PICKABLE_COLOR);
		pickables = pickables->next;
	}
}
