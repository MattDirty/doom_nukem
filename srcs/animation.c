/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfatton <lfatton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 05:54:53 by lfatton           #+#    #+#             */
/*   Updated: 2019/04/12 05:54:59 by lfatton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "animation.h"
#include "weapon.h"

void    reset_animation(t_animation *animation)
{
    animation->x_offset = 0;
    animation->y_offset = 0;
    animation->x_resize = 1;
    animation->y_resize = 1;
    animation->time = 0;
    animation->duration = 0;
}

void    start_animation(t_animation *animation, Uint32 duration)
{
    animation->time = 0;
    animation->duration = duration;
}
