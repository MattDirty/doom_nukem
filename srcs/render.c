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

#include "collision.h"
#include "doom.h"
#include "default.h"
#include "surface_manipulation.h"

static void	draw_wall(t_env *e, t_collision collision, Uint32 renderer_x)
{
    int			y;
    int			end;
    Uint32		color_text;
    t_segment	trunk_of_wall;
    double		dist_to_end_of_wall;
    t_coords	draw_text;
	double length;
	t_wall *wall;

	wall = collision.wall;

	length = RATIO / collision.distance * wall->height;

	y = e->p->vision_height - length / 2;
	end = e->p->vision_height + length / 2;
	trunk_of_wall = create_segment(collision.inters.x, collision.inters.y,
			collision.wall->segment.x1, collision.wall->segment.y1);

	dist_to_end_of_wall = get_segment_length(&trunk_of_wall) * PIXEL_UNIT;
	draw_text.x = (int)dist_to_end_of_wall % wall->texture->w;
	y = (y < 0 ? 0 : y);
	end = (end > WIN_H ? WIN_H : end);
	while (y < end)
	{
		put_pixel(e->doom->surface, renderer_x, y, color_text);
        draw_text.y = (y - e->p->vision_height + length / 2) * wall->texture->h / length;
        color_text = get_pixel(wall->texture, draw_text.x, draw_text.y, t_true);
		y++;
	}
}

static void draw_ceil_and_floor(t_sdl *doom, Uint32 renderer_x, double vision_height)
{
    int y;
    int end;

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

void		draw(
		t_env *e,
		double ray_angle,
		t_collision collision,
		Uint32 renderer_x)
{
	collision.distance *= cos(e->p->heading - ray_angle);

	draw_ceil_and_floor(e->doom, renderer_x, e->p->vision_height);
	draw_wall(e, collision, renderer_x);
}
