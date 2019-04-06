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

static void draw_flat(
		t_render *render, 
		t_collision *collision, 
		t_u_range range,
		SDL_Surface *texture)
{
    double      pixel_dist;
    double      weight;
	Uint32 x;
	Uint32 y;
    Uint32      color_text;
    Uint32      renderer_y;

	renderer_y = range.start;
    while (renderer_y < range.end)
	{
		pixel_dist = render->win_h / fabs(render->vision_height - renderer_y);
		weight = pixel_dist / collision->distance;
		x = (Uint32)(
				(weight * collision->inters.x
				+ (BLACK_MAGIC - weight) * render->p_pos.x)
				* texture->w) % texture->w;
		y = (Uint32)(
				(weight * collision->inters.y
				+ (BLACK_MAGIC - weight) * render->p_pos.y)
				* texture->h) % texture->h;
		color_text = get_pixel(texture, x, y, t_true);
		put_pixel(render->surface, render->x, renderer_y, color_text);
		renderer_y++;
	}
}

static void draw_ceil(
		t_render *render,
		t_collision *collision,
		t_u_range range,
		t_sector *current_sector)
{
	if (current_sector->open_sky)
	{
		skybox(render, range);
		return;
	}
	draw_flat(render, collision, range, current_sector->ceil);
}

static void         draw_wall(
		const t_render *render,
		const t_collision *collision, 
		const t_u_range range)
{
    Uint32		x;
    Uint32		y;
    Uint32		i;
    SDL_Surface *wall_text;

	if (collision->wall->type != e_wall)
		return;
	wall_text = collision->wall->pointer.texture;
	x = (Uint32)(get_distance_between_points(collision->inters.x,
	        collision->inters.y, collision->wall->segment.x1,
	        collision->wall->segment.y1) * wall_text->w) % wall_text->w;
	i = range.start;
	while (i < range.end)
	{
        y = ((i - render->vision_height + render->wall_height / 2)
        		* wall_text->h / render->wall_height);
        put_pixel(
        		render->surface, 
        		render->x, 
        		i, 
        		get_pixel(wall_text, x, y, t_true));
		i++;
	}
}

static t_render	fill_render_struct(t_env *e, Uint32 renderer_x)
{
	t_render render;

	render.surface = e->doom.surface;
	render.x = renderer_x;
	render.vision_height = e->p.vision_height;
	render.heading = e->p.heading;
	render.p_pos = e->p.pos;
	render.win_h = e->op.win_h;
	if (e->map->daytime)
		render.sky = e->map->daysky;
	else
		render.sky = e->map->nightsky;
	return (render);
}

void		draw(t_env *e, t_collisions *node, Uint32 renderer_x)
{
	t_u_range		range;
	t_u_range		prev_range;
	t_u_range		ceil_or_floor_range;
	t_render		r;
	t_sector		*current_sector;

	current_sector = e->p.current_sector;
	prev_range.start = 0;
	prev_range.end = e->op.win_h;
	r = fill_render_struct(e, renderer_x);
	while (node)
	{
		r.wall_height = e->op.ratio / node->item.distance * node->item.wall->height;
		range = wall_range(r.wall_height, r.vision_height, r.win_h);
		draw_wall(&r, &node->item, range);
		ceil_or_floor_range.start = range.end;
		ceil_or_floor_range.end = prev_range.end;
		draw_flat(&r, &node->item, ceil_or_floor_range, current_sector->floor);
		ceil_or_floor_range.start = prev_range.start;
		ceil_or_floor_range.end = range.start;
		draw_ceil(&r, &node->item, ceil_or_floor_range, current_sector);
		current_sector = get_next_sector_addr(current_sector, node->item.wall);
		node = node->next;
		prev_range = range;
	}
}
