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

static void	draw_wall(t_sdl *doom, t_collision collision, Uint32 renderer_x, double vision_height)
{
    int         y;
    int         end;
    Uint32		color_text;
    t_coords	draw_text;
	double      length;

	length = RATIO / collision.distance * collision.wall->height;
	y = vision_height - length / 2;
    y = (y < 0 ? 0 : y);
    end = vision_height + length / 2;
    end = (end > WIN_H ? WIN_H : end);
	draw_text.x = (int)(get_distance_between_points(collision.inters.x,
	        collision.inters.y, collision.wall->segment.x1,
	        collision.wall->segment.y1) * PIXEL_UNIT) % collision.wall->texture->w;
	while (y < end)
	{
        draw_text.y = (y - vision_height + length / 2)
                * collision.wall->texture->h / length;
        color_text = get_pixel(collision.wall->texture, draw_text.x, draw_text.y, t_true);
        put_pixel(doom->surface, renderer_x, y, color_text);
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
	draw_wall(e->doom, collision, renderer_x, e->p->vision_height);
}
