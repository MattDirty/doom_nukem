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

static void	draw_wall(t_env *e, double length, Uint32 renderer_x)
{
    int	y;
    int	end;
    Uint32	color_text;

	y = e->p->vision_height - length / 2;
	end = e->p->vision_height + length / 2;

	y = (y < 0 ? 0 : y);
	end = (end > WIN_H ? WIN_H : end);
	while (y < end)
	{
        e->sector->draw_text.y = (y - e->p->vision_height + length / 2) * 225 / length;
        color_text = get_pixel(e->sector->wall_text, e->sector->draw_text.x, e->sector->draw_text.y, t_true);
		put_pixel(e->doom->surface, renderer_x, y, int_to_t_color(color_text));
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
		put_pixel(doom->surface, renderer_x, y, int_to_t_color(SKYBLUE));
		y++;
	}
	y = vision_height;
	while (y < WIN_H)
	{
		put_pixel(doom->surface, renderer_x, y, int_to_t_color(BROWN));
		y++;
	}
}

void		draw(t_env *e, double ray_angle, t_collision collision, Uint32 renderer_x)
{
	double length;

	collision.distance *= cos(e->p->heading - ray_angle);
	length = RATIO / collision.distance * e->sector->wall_height;

	draw_ceil_and_floor(e->doom, renderer_x, e->p->vision_height);
	draw_wall(e, length, renderer_x);
}
