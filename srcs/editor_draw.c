/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_draw.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badhont <badhont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 19:50:23 by badhont           #+#    #+#             */
/*   Updated: 2019/04/12 03:21:32 by badhont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "default.h"
#include "editor.h"
#include "map.h"
#include "utils.h"
#include "struct_sdl.h"
#include "ui.h"
#include "utils.h"

void        draw_corners_editor(SDL_Surface *surface, t_segment *s)
{
    t_rect  rect;

    rect.width = CORNER_SIZE;
    rect.height = CORNER_SIZE;

    rect.pos.x = s->x1 - CORNER_SIZE / 2;
    rect.pos.y = s->y1 - CORNER_SIZE / 2;
    draw_rect(surface, &rect, L_BLUE);
    fill_rect(surface, &rect, L_BLUE);

    rect.pos.x = s->x2 - CORNER_SIZE / 2;
    rect.pos.y = s->y2 - CORNER_SIZE / 2;
    draw_rect(surface, &rect, L_BLUE);
    fill_rect(surface, &rect, L_BLUE);
}

void		draw_walls_editor(SDL_Surface *surface, t_walls *walls, t_i_coords map_offset, int zoom)
{
    int	i;
    t_segment s;

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

void        draw_enemies_in_sector_editor(SDL_Surface *target, t_enemies *enemies, t_i_coords map_offset, int zoom)
{
    int         i;
    t_coords    coords;

    i = 0;
    while (i < enemies->count)
    {
        coords.x = map_offset.x + enemies->items[i].object->x * zoom;
        coords.y = map_offset.y - enemies->items[i].object->y * zoom;
        draw_circle_filled(target, coords, 0.25 * zoom, PINK);
        i++;
    }
}

void        draw_objects_in_sector_editor(SDL_Surface *target, t_objects *objects, t_i_coords map_offset, int zoom)
{
    int         i;
    t_coords    coords;

    i = 0;
    while (i < objects->count)
    {
        coords.x = map_offset.x + objects->items[i].x * zoom;
        coords.y = map_offset.y - objects->items[i].y * zoom;
        draw_circle_filled(target, coords, 0.15 * zoom, GREEN);
        i++;
    }
}

void        draw_background(t_editor *ed)
{
    t_rect  background;

    background = create_rect(-1, -1, EDITOR_W + 1, EDITOR_H + 1);
    fill_rect(ed->sdl.surface, &background, BACKGROUND_COLOR);
}

void        draw_player_spawn(SDL_Surface *surface, t_coords spawn, t_i_coords map_offset, int zoom)
{
    t_coords coords;

    coords.x = map_offset.x + spawn.x * zoom;
    coords.y = map_offset.y - spawn.y * zoom;

    draw_circle_filled(surface, coords, 0.33 * zoom, PLAYER_COLOR);
}

void		draw_editor(t_editor *ed)
{
    int         i;

    i = 0;
    while (i < ed->map->sectors->count)
    {
        draw_walls_editor(ed->sdl.surface, ed->map->sectors->items[i].walls, ed->map_offset, ed->zoom);
        draw_objects_in_sector_editor(ed->sdl.surface, ed->map->sectors->items[i].objects, ed->map_offset, ed->zoom);
        draw_enemies_in_sector_editor(ed->sdl.surface, ed->map->sectors->items[i].enemies, ed->map_offset, ed->zoom);
        i++;
    }
    draw_player_spawn(ed->sdl.surface, ed->map->spawn, ed->map_offset, ed->zoom);
}
