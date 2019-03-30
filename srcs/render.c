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

void         draw_ceil(t_env *e, t_collision collision, Uint32 renderer_x, int y)
{
    double      pixel_dist;
    double      weight;
    t_coords    draw_text;
    Uint32      color_text;
    SDL_Surface *ceil;

    ceil = e->map->sectors->items[0].ceil;
    while (y >= 0)
    {
        pixel_dist = e->op.win_h / (e->p.vision_height - y);
        weight = (pixel_dist / collision.distance);
        draw_text.x = (Uint32)((weight * collision.inters.x + (3 - weight) * e->p.pos.x) * ceil->w) % ceil->w;
        draw_text.y = (Uint32)((weight * collision.inters.y + (3 - weight) * e->p.pos.y) * ceil->h) % ceil->h;
        color_text = get_pixel(ceil, draw_text.x, draw_text.y, t_true);
        put_pixel(e->doom.surface, renderer_x, y, color_text);
        y--;
    }
}

static void         draw_floor(t_env *e, t_collision collision, Uint32 renderer_x, Uint32 y)
{
    double      pixel_dist;
    double      weight;
    t_coords    draw_text;
    Uint32      color_text;
    SDL_Surface *floor;

    floor = e->map->sectors->items[0].floor;

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

static t_segment    draw_wall(t_env *e, t_collision collision, Uint32 renderer_x)
{
    t_segment   wall;
    Uint32		color_text;
    t_coords	draw_text;
    Uint32      y;

	wall.y1 = e->p.vision_height - collision.wall_length / 2;
	wall.y1 = (wall.y1 < 0 ? 0 : wall.y1);
    y = wall.y1;
	wall.y2 = e->p.vision_height + collision.wall_length / 2;
	wall.y2 = (wall.y2 > (int)e->op.win_h ? e->op.win_h : wall.y2);
	draw_text.x = (Uint32)(get_distance_between_points(collision.inters.x,
	        collision.inters.y, collision.wall->segment.x1,
	        collision.wall->segment.y1) * PIXEL_UNIT) % collision.wall->texture->w;
	while (y < wall.y2)
	{
        draw_text.y = (Uint32)((y - e->p.vision_height + collision.wall_length
                / 2) * collision.wall->texture->h / collision.wall_length);
        color_text = get_pixel(collision.wall->texture, draw_text.x, draw_text.y, t_true);
        put_pixel(e->doom.surface, renderer_x, y, color_text);
		y++;
	}
	return (wall);
}

void		draw(
		t_env *e,
		double ray_angle,
		t_collision collision,
		Uint32 renderer_x)
{
	t_segment   wall;

    collision.distance *= cos(e->p.heading - ray_angle);
	collision.wall_length = e->op.ratio / collision.distance * collision.wall->height;

    skybox(e, renderer_x);
	wall = draw_wall(e, collision, renderer_x);
    draw_floor(e, collision, renderer_x, (Uint32)wall.y2);
    if (!(e->map->sectors->items[0].open_sky))
       draw_ceil(e, collision, renderer_x, (int)wall.y1);
}
