/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_draw.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badhont <badhont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 19:50:23 by badhont           #+#    #+#             */
/*   Updated: 2019/04/17 23:59:22 by badhont          ###   ########.fr       */
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

void        draw_corners_editor(SDL_Surface *surface, t_segment *s)
{
    t_rect  rect;

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

void        draw_enemies_in_sector_editor(
        SDL_Surface *target,
        t_linked_enemies *enemies,
        t_i_coords map_offset,
        int zoom)
{
    t_coords    coords;

    while (enemies)
    {
        coords.x = map_offset.x + enemies->item.object->x * zoom;
        coords.y = map_offset.y - enemies->item.object->y * zoom;
        draw_circle_filled(target, coords, 5, ENEMY_COLOR);
        enemies = enemies->next;
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
        draw_circle_filled(target, coords, 3, OBJECT_COLOR);
        i++;
    }
}

void        draw_pickables_in_sector_editor(SDL_Surface *target, t_pickables *pickables, t_i_coords map_offset, int zoom)
{
    t_coords    coords;

    while (pickables)
    {
        coords.x = map_offset.x + pickables->item.object->x * zoom;
        coords.y = map_offset.y - pickables->item.object->y * zoom;
        draw_circle_filled(target, coords, 4, PICKABLE_COLOR);
        pickables = pickables->next;
    }
}

void        draw_background(t_editor *ed)
{
    t_rect  background;

    background = create_rect(-1, -1, EDITOR_W + 1, EDITOR_H + 1);
    fill_rect(ed->sdl.surface, &background, BACKGROUND_COLOR, e_false);
}

void        draw_player_spawn(SDL_Surface *surface, t_coords spawn, t_i_coords map_offset, int zoom)
{
    t_coords coords;

    coords.x = map_offset.x + spawn.x * zoom;
    coords.y = map_offset.y - spawn.y * zoom;

    draw_circle_filled(surface, coords, 6, PLAYER_COLOR);
}

void    show_possible_new_sector(t_editor *ed, int x, int y)
{
    t_segment   s1;
    t_segment   s2;
    t_segment   s3;
    Uint32      color;

    s3 = ed->selected.wall->segment;
    s1.x1 = ed->map_offset.x + s3.x1 * ed->zoom;
    s1.y1 = ed->map_offset.y - s3.y1 * ed->zoom;
    s1.x2 = x;
    s1.y2 = y;
    s2.x2 = ed->map_offset.x + s3.x2 * ed->zoom;
    s2.y2 = ed->map_offset.y - s3.y2 * ed->zoom;
    s2.x1 = x;
    s2.y1 = y;
    if (!new_node_pos_valid(ed,
            (t_coords){(double)(x - ed->map_offset.x) / ed->zoom,
                       (double)(ed->map_offset.y - y) / ed->zoom}))
        color = 0x969696FF;
    else
        color = 0x96FF0000;
    draw_segment(ed->sdl.surface, s1, color);
    draw_segment(ed->sdl.surface, s2, color);
}

void		draw_editor(t_editor *ed)
{
    int         i;
    int         mouse_x;
    int         mouse_y;

    i = 0;
    while (i < ed->map->sectors->count)
    {
        draw_walls_editor(ed->sdl.surface, ed->map->sectors->items[i]->walls, ed->map_offset, ed->zoom);
        draw_objects_in_sector_editor(ed->sdl.surface, ed->map->sectors->items[i]->objects, ed->map_offset, ed->zoom);
        draw_enemies_in_sector_editor(ed->sdl.surface, ed->map->sectors->items[i]->enemies, ed->map_offset, ed->zoom);
        draw_pickables_in_sector_editor(ed->sdl.surface, ed->map->sectors->items[i]->pickables, ed->map_offset, ed->zoom);
        i++;
    }
    draw_player_spawn(ed->sdl.surface, ed->map->spawn, ed->map_offset, ed->zoom);
    SDL_GetMouseState(&mouse_x, &mouse_y);
    if (mouse_x < PANEL_X)
    {
        if (ed->state == e_add_sector)
            show_possible_new_sector(ed, mouse_x, mouse_y);
    }
}
