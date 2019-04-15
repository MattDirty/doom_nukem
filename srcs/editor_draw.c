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



void		draw_walls_editor(SDL_Surface *surface, t_walls *walls)
{
    int	i;
    t_segment s2;
    t_segment s;
    //t_rect rect;

    i = 0;
    while (i < walls->count)
    {
        s = walls->items[i]->segment;
        s2.x1 = DRAW_MAP_X + s.x1 * EDITOR_ZOOM;
        s2.y1 = DRAW_MAP_Y - s.y1 * EDITOR_ZOOM;
        s2.x2 = DRAW_MAP_X + s.x2 * EDITOR_ZOOM;
        s2.y2 = DRAW_MAP_Y - s.y2 * EDITOR_ZOOM;
        if (walls->items[i]->type == e_portal)
            draw_segment(surface, s2, RED);
        else if (walls->items[i]->type == e_wall)
            draw_segment(surface, s2, WHITE);
        else if (walls->items[i]->type == e_transparent_wall)
            draw_segment(surface, s2, BLUE);
        draw_corners_editor(surface, &s2);
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
        coords.x = DRAW_MAP_X + enemies->items[i].object->x * EDITOR_ZOOM;
        coords.y = DRAW_MAP_Y - enemies->items[i].object->y * EDITOR_ZOOM;
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
        coords.x = DRAW_MAP_X + objects->items[i].x * EDITOR_ZOOM;
        coords.y = DRAW_MAP_Y - objects->items[i].y * EDITOR_ZOOM;
        draw_circle_filled(target, coords, 0.15 * EDITOR_ZOOM, GREEN);
        i++;
    }
}

void        draw_background(t_editor *ed)
{
    t_rect  background;

    background = create_rect(-1, -1, EDITOR_W + 1, EDITOR_H + 1);
    fill_rect(ed->sdl.surface, &background, BACKGROUND_COLOR);
}

void        draw_player_spawn(SDL_Surface *surface, t_coords spawn)
{
    t_coords coords;

    coords.x = DRAW_MAP_X + spawn.x * EDITOR_ZOOM;
    coords.y = DRAW_MAP_Y - spawn.y * EDITOR_ZOOM;

    draw_circle_filled(surface, coords, 0.33 * EDITOR_ZOOM, PLAYER_COLOR);
}

void		draw_editor(t_editor *ed)
{
    int         i;

    i = 0;
    while (i < ed->map->sectors->count)
    {
        draw_walls_editor(ed->sdl.surface, ed->map->sectors->items[i].walls);
        draw_objects_in_sector_editor(ed->sdl.surface, ed->map->sectors->items[i].objects);
        draw_enemies_in_sector_editor(ed->sdl.surface, ed->map->sectors->items[i].enemies);
        i++;
    }
    draw_player_spawn(ed->sdl.surface, ed->map->spawn);
}
