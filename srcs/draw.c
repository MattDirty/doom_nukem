/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfatton <lfatton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 00:51:49 by lfatton           #+#    #+#             */
/*   Updated: 2019/03/08 18:31:36 by lfatton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static void	draw_wall(t_env *e, int start, int end)
{
    int y;

    int color[4]; //debug
    color[0] = 0xFF000000;
    color[1] = 0xFFFF0000;
    color[2] = 0xFFFFFF00;
    color[3] = 0xFFFFFFFF;

    y = start;
	while (y < end)
	{
		put_pixel(e->surf, e->col, y, color[e->sector->wall_id]);
		y++;
	}
}

static void	draw_ceil_and_floor(t_env *e)
{
	int	y;
	int	end;
	
	y = 0;
	end = e->p->height;
	while (y < end)
	{
		put_pixel(e->surf, e->col, y, SKYBLUE);
		y++;
	}
	y = e->p->height;
	while (y < WIN_H)
	{
		put_pixel(e->surf, e->col, y, BROWN);
		y++;
	}
}

void		draw(t_env *e, double ray_angle, double distance)
{
	int start;
	int end;
	double length;

	distance *= cos(e->p->heading - ray_angle); //fisheye correction
	length = RATIO / distance;

	draw_ceil_and_floor(e);

	start = e->p->height - length / 2;
	end = e->p->height + length / 2;

	start = (start < 0 ? 0 : start);
	end = (end > WIN_H ? WIN_H : end);

	draw_wall(e, start, end);
}
