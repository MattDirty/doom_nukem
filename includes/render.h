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
# include "doom.h"

# define BLACK_MAGIC 3

typedef struct  s_render
{
    t_env		*bandaid;
    SDL_Surface *surface;
    Uint32      x;
    double      wall_height;
    double      vision_height;
    double      heading;
    t_coords    p_pos;
    Uint32      win_h;
    SDL_Surface *sky;
    enum e_bool	lights;
    double		light_value;
}               t_render;

void        draw(t_env *e, t_collisions *collisions, Uint32 rdr_x);
enum e_bool day_to_night(double ms_since_update, t_params daytime);
void        skybox(const t_render *render, t_u_range range);

#endif
