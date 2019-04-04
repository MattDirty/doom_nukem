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

static t_i_segment  get_wall_vertical_length(double wall_length, double vision_height, int win_h)
{
    t_i_segment wall;

    wall.y1 = vision_height - wall_length / 2;
    wall.y1 = (wall.y1 < 0 ? 0 : wall.y1);
    wall.y2 = vision_height + wall_length / 2;
    wall.y2 = (wall.y2 > win_h ? win_h : wall.y2);
    return (wall);
}

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

static void draw_ceil_and_floor(t_render render, t_collision collision, t_i_segment wall,
                                enum e_bool portal)
{
    SDL_Surface *ceil;
    SDL_Surface *floor;
    enum e_bool open_sky;

    if (!portal)
    {
        ceil = render.current_sector->ceil;
        floor = render.current_sector->floor;
        open_sky = render.current_sector->open_sky;
    }
    else
    {
        ceil = render.next_sector->ceil;
        floor = render.next_sector->floor;
        open_sky = render.next_sector->open_sky;
    }
    if (!open_sky)
    {
        while (wall.y1 >= 0)
        {
            draw_flat(render, collision, wall.y1, ceil);
            wall.y1--;
        }
    }
    while (wall.y2 < render.win_h)
    {
        draw_flat(render, collision, wall.y2, floor);
        wall.y2++;
    }
}

static void         draw_wall(t_render render, t_collision collision, t_i_segment wall)
{
    Uint32      color_text;
    t_coords    draw_text;
    SDL_Surface *wall_text;

	wall_text = collision.wall->pointer.texture;
	draw_text.x = (Uint32)(get_distance_between_points(collision.inters.x,
	        collision.inters.y, collision.wall->segment.x1,
	        collision.wall->segment.y1) * wall_text->w) % wall_text->w;
	while (wall.y1 < wall.y2)
	{
        draw_text.y = (Uint32)((wall.y1 - render.vision_height
                + render.wall_length / 2) * wall_text->h / render.wall_length);
        color_text = get_pixel(wall_text, draw_text.x, draw_text.y, t_true);
        put_pixel(render.surface, render.x, wall.y1, color_text);
		wall.y1++;
	}
}

void		draw(t_env *e, t_collision collision, Uint32 renderer_x, t_ray ray)
{
	t_i_segment wall;
    t_render    render;
//    t_coords    portal_inters;
//    double      distance;
//    double      wall_length;

    render.surface = e->doom.surface;
    render.x = renderer_x;
    render.wall_length = e->op.ratio / collision.distance * collision.wall->height;
    render.vision_height = e->p.vision_height;
    render.heading = e->p.heading;
    render.p_pos = e->p.pos;
    render.win_h = e->op.win_h;
    render.current_sector = e->p.current_sector;
    render.map = *e->map;
	(void)ray;

    wall = get_wall_vertical_length(render.wall_length, render.vision_height, render.win_h);
    skybox(render);
    draw_wall(render, collision, wall);
//    if (collision.first_portal)
//    {
//        render.next_sector = get_next_sector_addr(render.current_sector, collision.first_portal);
//        draw_ceil_and_floor(render, collision, wall, t_true);
//        segments_intersect(&ray.seg, &collision.first_portal->segment, &portal_inters);
//        distance = get_distance_between_points(ray.seg.x1, ray.seg.y1, portal_inters.x, portal_inters.y);
//        distance *= cos(e->p.heading - ray.angle);
//        wall_length = e->op.ratio / distance * collision.wall->height;
//        wall = get_wall_vertical_length(wall_length, render.vision_height, render.win_h);
//    }
		draw_ceil_and_floor(render, collision, wall, t_false);
}
