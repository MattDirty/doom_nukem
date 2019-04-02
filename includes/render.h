/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfatton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/29 23:13:18 by lfatton           #+#    #+#             */
/*   Updated: 2019/03/29 23:13:20 by lfatton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# include "doom.h"
# include "timer_handler.h"
# include "collision.h"
# include "SDL.h"

# define BLACK_MAGIC 3

typedef struct  s_render
{
    SDL_Surface *surface;
    Uint32      x;
    double      wall_length;
    double      vision_height;
    double      heading;
    t_coords    p_pos;
    int         win_h;
    t_sector    current_sector;
    t_map       map;
}               t_render;

void        draw(t_env *e, double ray_ang, t_collision col, Uint32 rdr_x);
enum e_bool day_to_night(double ms_since_update, t_params daytime);
void        skybox(t_render render);

#endif