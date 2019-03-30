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
#include "skybox.h"
#include "surface_manipulation.h"

static void	draw_floor(t_env *e, t_collision collision, Uint32 renderer_x, SDL_Surface *floor)
{
    double      pixel_dist;
    double      weight;
    t_coords    draw_text;
    Uint32      color_text;
    Uint32      y;

    y = e->p.vision_height + collision.wall_length / 2 + 1;
    while (y < WIN_H)
    {
        pixel_dist = e->op.win_h / (y - e->p.vision_height);
        weight = (pixel_dist / collision.distance);
        draw_text.x = (Uint32)((weight * collision.inters.x + (3 - weight) * e->p.pos.x) * floor->w) % floor->w;
        draw_text.y = (Uint32)((weight * collision.inters.y + (3 - weight) * e->p.pos.y) * floor->h) % floor->h;
        color_text = get_pixel(floor, draw_text.x, draw_text.y, t_true);
        put_pixel(e->doom.surface, renderer_x, y, color_text);
        y++;
    }
}

static void	draw_wall(t_env *e, t_collision collision, Uint32 renderer_x, double vision_height)
{
    int         y;
    int         end;
    Uint32		color_text;
    t_coords	draw_text;

	y = vision_height - collision.wall_length / 2;
    y = (y < 0 ? 0 : y);
    end = vision_height + collision.wall_length / 2;
	end = (end > e->op.win_h ? e->op.win_h : end);
	draw_text.x = (int)(get_distance_between_points(collision.inters.x,
	        collision.inters.y, collision.wall->segment.x1,
	        collision.wall->segment.y1) * PIXEL_UNIT) % collision.wall->texture->w;
	while (y < end)
	{
        draw_text.y = (y - vision_height + collision.wall_length / 2)
                * collision.wall->texture->h / collision.wall_length;
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

void		draw(
		t_env *e,
		double ray_angle,
		t_collision collision,
		Uint32 renderer_x)
{
	collision.distance *= cos(e->p.heading - ray_angle);
	collision.wall_length = e->op.ratio / collision.distance * collision.wall->height;

    paint_floor(e, &e->op, renderer_x, e->p.vision_height);
    skybox(e, renderer_x);
	draw_wall(e, collision, renderer_x, e->p.vision_height);
    draw_floor(e, collision, renderer_x, e->derp);
}
