/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfatton <lfatton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 05:36:54 by lfatton           #+#    #+#             */
/*   Updated: 2019/04/12 05:37:02 by lfatton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ANIMATION_H
# define ANIMATION_H

# include "SDL.h"

typedef struct  s_animation
{
    int     x_offset;
    int     y_offset;
    double  x_resize;
    double  y_resize;
    double  duration;
    double  time;
}               t_animation;

void    reset_animation(t_animation *animation);
void    start_animation(t_animation *animation, Uint32 duration);

#endif
