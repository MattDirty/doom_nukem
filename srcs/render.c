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

static void	draw_wall(t_env *e, t_collision collision, Uint32 renderer_x, double vision_height)
{
    int         y;
    int         end;
    Uint32		color_text;
    t_coords	draw_text;
	double      length;

	length = e->op.ratio / collision.distance * collision.wall->height;
	y = vision_height - length / 2;
    y = (y < 0 ? 0 : y);
    end = vision_height + length / 2;
    end = (end > (int)e->op.win_h ? e->op.win_h : end);
	draw_text.x = (int)(get_distance_between_points(collision.inters.x,
	        collision.inters.y, collision.wall->segment.x1,
	        collision.wall->segment.y1) * PIXEL_UNIT) % collision.wall->texture->w;
	while (y < end)
	{
        draw_text.y = (y - vision_height + length / 2)
                * collision.wall->texture->h / length;
        color_text = get_pixel(collision.wall->texture, draw_text.x, draw_text.y, t_true);
        put_pixel(e->doom.surface, renderer_x, y, color_text);
		y++;
	}
}

static void paint_floor(t_env *e, t_config *op, Uint32 renderer_x, double vision_height)
{
    Uint32  y;

    y = vision_height;
    while (y < op->win_h)
    {
        put_pixel(e->doom.surface, renderer_x, y, BROWN);
        y++;
    }
}

static void skybox(t_env *e, Uint32 renderer_x)
{
    Uint32  y;
    Uint32  end;
    Uint32	color_text;
    t_coords	draw_text;

    y = 0;
    end = e->p.vision_height;
    draw_text.x = e->map->daysky->w / CIRCLE * e->p.heading + renderer_x;
    while (y < end)
    {
        draw_text.y = (e->op.win_h - fabs(e->p.vision_height - y))
                * e->map->daysky->h / e->op.win_h;
        color_text = get_pixel(e->map->daysky, draw_text.x, draw_text.y, t_true);
        put_pixel(e->doom.surface, renderer_x, y, color_text);
        y++;
    }
}

void		draw(
		t_env *e,
		double ray_angle,
		t_collision collision,
		Uint32 renderer_x)
{
	collision.distance *= cos(e->p.heading - ray_angle);

	paint_floor(e, &e->op, renderer_x, e->p.vision_height);
	skybox(e, renderer_x);
	draw_wall(e, collision, renderer_x, e->p.vision_height);
}
