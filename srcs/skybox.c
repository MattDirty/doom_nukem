/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skybox.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfatton <lfatton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/29 23:07:46 by lfatton           #+#    #+#             */
/*   Updated: 2019/03/29 23:07:49 by lfatton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "timer_handler.h"
#include <SDL.h>
#include "default.h"
#include "render.h"
#include "render_blackhole.h"
#include "surface_manipulation.h"
#include "ui.h"
#include <math.h>

enum e_bool    day_to_night(double ms_since_update, t_params daytime)
{
    (void)ms_since_update;
    if (*(enum e_bool*)daytime)
        *(enum e_bool*)daytime = e_false;
    else
        *(enum e_bool*)daytime = e_true;
    return (e_true);
}

void     draw_sun_or_moon(SDL_Surface *surface, t_map *map, t_config *op)
{
    t_i_coords    pos;

    pos.x = op->win_w - 50;
    pos.y = 0;
    if (map->daytime)
        draw_on_screen(surface, map->hud.sun, pos, e_true);
    else
        draw_on_screen(surface, map->hud.moon, pos, e_true);
}

void            skybox(const t_render *render, t_u_range range)
{
    Uint32 y;
    Uint32 end;
    Uint32 color_text;
    t_coords draw_text;

    y = range.start;
    end = range.end;
    draw_text.x = render->sky->w / CIRCLE * render->heading + render->x;
    while (y < end)
    {
        draw_text.y = fabs((render->win_h - 1) - fabs(render->vision_height - y))
        		* render->sky->h / render->win_h;
        color_text = get_pixel(render->sky, draw_text.x, draw_text.y, e_true);
        put_pixel_blackhole(render->bandaid, render->x, y, color_text);
        y++;
    }
}
