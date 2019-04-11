/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_draw.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badhont <badhont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 19:50:23 by badhont           #+#    #+#             */
/*   Updated: 2019/04/11 20:20:46 by badhont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor_draw.h"
#include "default.h"
#include "editor.h"
#include "map.h"
#include "struct_sdl.h"

void		draw_walls_editor(SDL_Surface *surface, t_walls *walls)
{
    int	i;
    t_segment s2;
    t_segment s;

    i = 0;
    while (i < walls->count)
    {
        s = walls->items[i]->segment;
        s2.x1 = EDITOR_W_H + s.x1 * EDITOR_ZOOM;
        s2.y1 = EDITOR_H_H - s.y1 * EDITOR_ZOOM;
        s2.x2 = EDITOR_W_H + s.x2 * EDITOR_ZOOM;
        s2.y2 = EDITOR_H_H - s.y2 * EDITOR_ZOOM;
        if (walls->items[i]->type == e_portal)
            draw_segment(surface, s2, RED);
        else if (walls->items[i]->type == e_wall)
            draw_segment(surface, s2, WHITE);
        else if (walls->items[i]->type == e_transparent_wall)
            draw_segment(surface, s2, BLUE);
        i++;
    }
}

void        draw_enemies_in_sector_editor(SDL_Surface *target, t_enemies *enemies)
{
    int         i;
    t_coords    coords;

    i = 0;
    while (i < enemies->count)
    {
        coords.x = EDITOR_W_H + enemies->items[i].object->x * EDITOR_ZOOM;
        coords.y = EDITOR_H_H - enemies->items[i].object->y * EDITOR_ZOOM;
        draw_circle_filled(target, coords, 0.25 * EDITOR_ZOOM, PINK);
        i++;
    }
}

void        draw_objects_in_sector_editor(SDL_Surface *target, t_objects *objects)
{
    int         i;
    t_coords    coords;

    i = 0;
    while (i < objects->count)
    {
        coords.x = EDITOR_W_H + objects->items[i].x * EDITOR_ZOOM;
        coords.y = EDITOR_H_H - objects->items[i].y * EDITOR_ZOOM;
        draw_circle_filled(target, coords, 0.15 * EDITOR_ZOOM, GREEN);
        i++;
    }
}

void        draw_corners_editor(SDL_Surface *surface, t_walls *walls)
{
    (void)surface;
    (void)walls;
}

void		draw_editor(t_editor *ed)
{
    int i;

    i = 0;
    while (i < ed->map->sectors->count)
    {
        draw_walls_editor(ed->sdl.surface, ed->map->sectors->items[i].walls);
        draw_corners_editor(ed->sdl.surface, ed->map->sectors->items[i].walls);
        draw_objects_in_sector_editor(ed->sdl.surface, ed->map->sectors->items[i].objects);
        draw_enemies_in_sector_editor(ed->sdl.surface, ed->map->sectors->items[i].enemies);
        i++;
    }
}