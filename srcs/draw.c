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
		put_pixel(e->surf, e->col, y, color[e->wall_id]);
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
	while (y < WIN_H - 1)
	{
		put_pixel(e->surf, e->col, y, BROWN);
		y++;
	}
}

void		draw(t_env *e, double distance)
{
	int start;
	int end;

	e->r->dist = distance * cos(e->p->heading - e->r->ang); //fisheye correction
	e->r->length = RATIO / e->r->dist;
	draw_ceil_and_floor(e);

	start = e->p->height - e->r->length / 2 + 1;
	end = e->p->height + e->r->length / 2;

	start = (start < 0 ? 0 : start);
	end = (end >= WIN_H ? WIN_H - 1 : end);

	draw_wall(e, start, end);
}
