/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skybox.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfatton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/29 23:07:46 by lfatton           #+#    #+#             */
/*   Updated: 2019/03/29 23:07:49 by lfatton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "timer_handler.h"
#include "SDL.h"
#include "default.h"
#include "render.h"
#include "surface_manipulation.h"

enum e_bool    day_to_night(double ms_since_update, t_params daytime)
{
    (void)ms_since_update;
    if (*(enum e_bool*)daytime)
        *(enum e_bool*)daytime = t_false;
    else
        *(enum e_bool*)daytime = t_true;
    return (t_true);
}

void            skybox(t_render render)
{
    Uint32 y;
    Uint32 end;
    Uint32 color_text;
    t_coords draw_text;
    SDL_Surface *sky;

    if (render.map.daytime)
        sky = render.map.daysky;
    else
        sky = render.map.nightsky;
    y = 0;
    end = render.vision_height;
    draw_text.x = sky->w / CIRCLE * render.heading + render.x;
    while (y < end) {
        draw_text.y = (render.win_h - fabs(render.vision_height - y)) * sky->h
                      / render.win_h;
        color_text = get_pixel(sky, draw_text.x, draw_text.y, t_true);
        put_pixel(render.surface, render.x, y, color_text);
        y++;
    }
}
