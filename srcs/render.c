/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfatton <lfatton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 00:51:49 by lfatton           #+#    #+#             */
/*   Updated: 2019/03/08 18:31:36 by lfatton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static void	draw_wall(t_env *e, int start, int end, Uint32 renderer_x)
{
    int y;

    int color[8]; //debug
	color[0] = 0xFF000000;
	color[1] = 0xFFFF0000;
	color[2] = 0xFFFFFF00;
	color[3] = 0xFFFFFFFF;
	color[4] = 0xFF000000;
	color[5] = 0xFFFF0000;
	color[6] = 0xFFFFFF00;
	color[7] = 0xFFFFFFFF;

    y = start;
	while (y < end)
	{
		put_pixel(e->doom->surface, renderer_x, y, color[e->sector->wall_id]);
		y++;
	}
}

static void	draw_ceil_and_floor(t_sdl *doom, Uint32 renderer_x, double vision_height)
{
	int	y;
	int	end;
	
	y = 0;
	end = vision_height;
	while (y < end)
	{
		put_pixel(doom->surface, renderer_x, y, SKYBLUE);
		y++;
	}
	y = vision_height;
	while (y < WIN_H)
	{
		put_pixel(doom->surface, renderer_x, y, BROWN);
		y++;
	}
}

void		draw(t_env *e, double ray_angle, double distance, Uint32 renderer_x)
{
	int start;
	int end;
	double length;

	distance *= cos(e->p->heading - ray_angle); //fisheye correction
	length = RATIO / distance * e->sector->wall_height;

	draw_ceil_and_floor(e->doom, renderer_x, e->p->vision_height);

	start = e->p->vision_height - length / 2;
	end = e->p->vision_height + length / 2;

	start = (start < 0 ? 0 : start);
	end = (end > WIN_H ? WIN_H : end);

	draw_wall(e, start, end, renderer_x);
}
