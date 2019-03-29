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

void            skybox(t_env *e, Uint32 renderer_x)
{
    Uint32 y;
    Uint32 end;
    Uint32 color_text;
    t_coords draw_text;
    SDL_Surface *sky;

    if (e->map->daytime)
        sky = e->map->daysky;
    else
        sky = e->map->nightsky;
    y = 0;
    end = e->p.vision_height;
    draw_text.x = sky->w / CIRCLE * e->p.heading + renderer_x;
    while (y < end) {
        draw_text.y = (e->op.win_h - fabs(e->p.vision_height - y)) * sky->h
                      / e->op.win_h;
        color_text = get_pixel(sky, draw_text.x, draw_text.y, t_true);
        put_pixel(e->doom.surface, renderer_x, y, color_text);
        y++;
    }
}
