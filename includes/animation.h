/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badhont <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 01:07:18 by badhont           #+#    #+#             */
/*   Updated: 2019/04/19 07:41:23 by badhont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ANIMATION_H
# define ANIMATION_H

# include <SDL.h>

typedef struct s_animation		t_animation;

struct							s_animation
{
	int			x_offset;
	int			y_offset;
	double		x_resize;
	double		y_resize;
	double		duration;
	double		time;
};

void							reset_animation(t_animation *animation);
void							start_animation(t_animation *animation,
								Uint32 duration);

#endif
