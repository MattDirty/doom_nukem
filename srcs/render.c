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
#include "render.h"
#include "surface_manipulation.h"

static void draw_flat(t_render render, t_collision collision, int y, SDL_Surface *flat)
{
    double      pixel_dist;
    double      weight;
    t_coords    draw_text;
    Uint32      color_text;

    pixel_dist = render.win_h / fabs(render.vision_height - y);
    weight = (pixel_dist / collision.distance);
    draw_text.x = (Uint32)((weight * collision.inters.x + (BLACK_MAGIC - weight)
            * render.p_pos.x) * flat->w) % flat->w;
    draw_text.y = (Uint32)((weight * collision.inters.y + (BLACK_MAGIC - weight)
            * render.p_pos.y) * flat->h) % flat->h;
    color_text = get_pixel(flat, draw_text.x, draw_text.y, t_true);
    put_pixel(render.surface, render.x, y, color_text);
}

static void draw_ceil_and_floor(t_render render, t_collision collision, t_i_segment wall)
{
    if (!(render.current_sector.open_sky))
    {
        while (wall.y1 >= 0)
        {
            draw_flat(render, collision, wall.y1, render.current_sector.ceil);
            wall.y1--;
        }
    }
    while (wall.y2 < render.win_h)
    {
        draw_flat(render, collision, wall.y2, render.current_sector.floor);
        wall.y2++;
    }
}

static t_i_segment  draw_wall(t_render render, t_collision collision)
{
    t_i_segment wall;
    Uint32      color_text;
    t_coords    draw_text;
    int         y;
    SDL_Surface *wall_text;

	wall_text = collision.wall->pointer.texture;
    wall.y1 = render.vision_height - render.wall_length / 2;
	wall.y1 = (wall.y1 < 0 ? 0 : wall.y1);
    y = wall.y1;
	wall.y2 = render.vision_height + render.wall_length / 2;
	wall.y2 = (wall.y2 > render.win_h ? render.win_h : wall.y2);
	draw_text.x = (Uint32)(get_distance_between_points(collision.inters.x,
	        collision.inters.y, collision.wall->segment.x1,
	        collision.wall->segment.y1) * wall_text->w) % wall_text->w;
	while (y < wall.y2)
	{
        draw_text.y = (Uint32)((y - render.vision_height + render.wall_length
                / 2) * wall_text->h / render.wall_length);
        color_text = get_pixel(wall_text, draw_text.x, draw_text.y, t_true);
        put_pixel(render.surface, render.x, y, color_text);
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
	t_i_segment wall;
    t_render    render;

    collision.distance *= cos(e->p.heading - ray_angle);
    render.surface = e->doom.surface;
    render.x = renderer_x;
    render.wall_length = e->op.ratio / collision.distance * collision.wall->height;
    render.vision_height = e->p.vision_height;
    render.heading = e->p.heading;
    render.p_pos = e->p.pos;
    render.win_h = e->op.win_h;
    render.current_sector = *e->p.current_sector;
    render.map = *e->map;

    skybox(render);
	wall = draw_wall(render, collision);
    draw_ceil_and_floor(render, collision, wall);
}
