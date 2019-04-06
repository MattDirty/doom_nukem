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
#include <math.h>

enum e_bool    day_to_night(double ms_since_update, t_params daytime)
{
    (void)ms_since_update;
    if (*(enum e_bool*)daytime)
        *(enum e_bool*)daytime = t_false;
    else
        *(enum e_bool*)daytime = t_true;
    return (t_true);
}

void            skybox(t_render *render, t_u_range range)
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
        draw_text.y = (render->win_h - fabs(render->vision_height - y))
        		* render->sky->h / render->win_h;
        color_text = get_pixel(render->sky, draw_text.x, draw_text.y, t_true);
        put_pixel(render->surface, render->x, y, color_text);
        y++;
    }
}
