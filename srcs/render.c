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

static t_u_range wall_range(double wall_height, double vision_height, Uint32 win_h)
{
    t_u_range wall;

    if (vision_height < wall_height / 2)
    	wall.start = 0;
    else
    	wall.start = vision_height - wall_height / 2;
    wall.end = vision_height + wall_height / 2;
    wall.end = (wall.end > win_h ? win_h : wall.end);
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

static void draw_ceil_and_floor(t_render render, t_collision collision, t_u_range range,
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
        while (range.start != 0)
        {
            draw_flat(render, collision, range.start, ceil);
			range.start--;
        }
    }
    while (range.end < render.win_h)
    {
        draw_flat(render, collision, range.end, floor);
		range.end++;
    }
}

static void         draw_wall(const t_render render, const t_collision collision, const t_u_range range)
{
    Uint32		x;
    Uint32		y;
    Uint32		i;
    SDL_Surface *wall_text;

	wall_text = collision.wall->pointer.texture;
	x = (Uint32)(get_distance_between_points(collision.inters.x,
	        collision.inters.y, collision.wall->segment.x1,
	        collision.wall->segment.y1) * wall_text->w) % wall_text->w;
	i = range.start;
	while (i < range.end)
	{
        y = ((i - render.vision_height + render.wall_height / 2)
        		* wall_text->h / render.wall_height);
        put_pixel(render.surface, render.x, i, get_pixel(wall_text, x, y, t_true));
		i++;
	}
}

t_render	fill_render_struct(t_env *e, Uint32 renderer_x)
{
	t_render render;

	render.surface = e->doom.surface;
	render.current_sector = e->p.current_sector;
	render.x = renderer_x;
	render.vision_height = e->p.vision_height;
	render.heading = e->p.heading;
	render.p_pos = e->p.pos;
	render.win_h = e->op.win_h;
	render.map = *e->map;
	return (render);
}

void		draw(t_env *e, t_collisions *collisions, Uint32 renderer_x, t_ray ray)
{
	t_u_range		range;
	t_render		render;
	t_collisions	*ptr;

	(void)ray;
	ptr = collisions;
	render = fill_render_struct(e, renderer_x);
	skybox(render);
	while (ptr)
	{
		render.wall_height = e->op.ratio / ptr->item.distance * ptr->item.wall->height;
		range = wall_range(render.wall_height, render.vision_height, render.win_h);
		if (ptr->item.wall->type == e_wall)
		{
			draw_wall(render, ptr->item, range);
			draw_ceil_and_floor(render, ptr->item, range, t_false);
		}
		else if (ptr->item.wall->type == e_portal)
		{
			render.next_sector = get_next_sector_addr(render.current_sector, ptr->item.wall);
			draw_ceil_and_floor(render, ptr->item, range, t_true);
			render.current_sector = render.next_sector;
		}
		ptr = ptr->next;
	}
}
