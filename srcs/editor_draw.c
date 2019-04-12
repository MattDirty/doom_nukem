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

#include "editor_draw.h"
#include "default.h"
#include "editor.h"
#include "map.h"
#include "utils.h"
#include "struct_sdl.h"
#include "ui.h"

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

void        draw_pannel(SDL_Surface *target)
{
    t_rect  pannel;

    pannel = create_rect(PANNEL_X, PANNEL_Y,
            EDITOR_W - PANNEL_X - 1, EDITOR_H - 1);
    draw_rect(target, &pannel, WHITE);
    fill_rect(target, &pannel, DARK_BLUE);
}

void        draw_save_button(SDL_Surface *target, t_buttons *buttons, int i)
{
    t_button    save_btn;
    SDL_Surface *save;
    t_coords    location;

    save_btn.rect = create_rect(PANNEL_X + 5, PANNEL_Y + 5, 40, 20);
    draw_rect(target, &save_btn.rect, RED);
    fill_rect(target, &save_btn.rect, PINK);
    save = write_text("fonts/sixty.ttf", 15, "SAVE", (SDL_Colour){255,0,0,255});
    location.x = save_btn.rect.pos.x + save_btn.rect.width / 2 - save->w / 2;
    location.y = save_btn.rect.pos.y + save_btn.rect.height / 2 - save->h / 2;
    draw_on_screen(target, save, location, t_false);
    free(save);
    buttons->items[i] = save_btn;
}

void		draw_editor(t_editor *ed)
{
    t_buttons   buttons;
    int         i;

    i = 0;
    buttons.count = 1;
    draw_pannel(ed->sdl.surface);
    while (i < ed->map->sectors->count)
    {
        draw_walls_editor(ed->sdl.surface, ed->map->sectors->items[i].walls);
        draw_objects_in_sector_editor(ed->sdl.surface, ed->map->sectors->items[i].objects);
        draw_enemies_in_sector_editor(ed->sdl.surface, ed->map->sectors->items[i].enemies);
        i++;
    }
    draw_save_button(ed->sdl.surface, &buttons, 0);
}