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

static void	draw_wall(t_env *e)
{
    int color[4]; //debug
    color[0] = 0xFF000000;
    color[1] = 0xFFFF0000;
    color[2] = 0xFFFFFF00;
    color[3] = 0xFFFFFFFF;
	while (e->start < e->end)
	{
		put_pixel(e->surf, e->col, e->start, color[e->wall_id]);
		e->start++;
	}
}

static void	draw_ceil_and_floor(t_env *e)
{
	e->start = 0;
	e->end = e->p->height;
	e->color = SKYBLUE;
	while (e->start < e->end)
	{
		put_pixel(e->surf, e->col, e->start, e->color);
		e->start++;
	}
	e->start = e->p->height;
	e->end = WIN_H - 1;
	e->color = BROWN;
	while (e->start < e->end)
	{
		put_pixel(e->surf, e->col, e->start, e->color);
		e->start++;
	}
}

void		draw(t_env *e)
{
	e->r->dist *= cos(e->p->heading - e->r->ang); //fisheye correction
	e->r->length = RATIO / e->r->dist;
	draw_ceil_and_floor(e);
	e->start = e->p->height - e->r->length / 2 + 1;
	e->end = e->p->height + e->r->length / 2;
	e->start = (e->start < 0 ? 0 : e->start);
	e->end = (e->end >= WIN_H ? WIN_H - 1 : e->end);
	draw_wall(e);
}
