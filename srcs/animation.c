/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfatton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 05:27:23 by lfatton           #+#    #+#             */
/*   Updated: 2019/04/19 05:31:08 by lfatton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "animation.h"
#include "weapon.h"

void	reset_animation(t_animation *animation)
{
	animation->x_offset = 0;
	animation->y_offset = 0;
	animation->x_resize = 1;
	animation->y_resize = 1;
	animation->time = 0;
	animation->duration = 0;
}

void	start_animation(t_animation *animation, Uint32 duration)
{
	animation->time = 0;
	animation->duration = duration;
}
