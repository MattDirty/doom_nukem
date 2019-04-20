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

enum e_bool	animate_door(double ms_since_update, t_params params)
{
	t_door_animation	*animation;

	animation = (t_door_animation *)params;
	animation->elapsed_time += ms_since_update;
	animation->door->wall_offset = (animation->elapsed_time
			/ animation->total_time * animation->target_offset);
	if (animation->elapsed_time >= animation->total_time)
	{
		if (!animation->door->to_infinity)
			animation->door->type = e_portal;
		free(animation);
		return (e_false);
	}
	return (e_true);
}

enum e_bool	unlock(double ms_since_update, t_params ready)
{
	(void)ms_since_update;
	*(enum e_bool *)ready = e_true;
	return (e_false);
}

void		reset_animation(t_animation *animation)
{
	animation->x_offset = 0;
	animation->y_offset = 0;
	animation->x_resize = 1;
	animation->y_resize = 1;
	animation->time = 0;
	animation->duration = 0;
}

void		start_animation(t_animation *animation, Uint32 duration)
{
	animation->time = 0;
	animation->duration = duration;
}
