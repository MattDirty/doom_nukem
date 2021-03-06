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
#include "render_blackhole.h"
#include "surface_manipulation.h"
#include <math.h>

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
	Uint32 		x;
	Uint32 		y;
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
		color_text = get_pixel(texture, x, y, e_true);
		put_pixel_blackhole(render->bandaid, render->x, renderer_y, color_text);
		if (render->lights)
			put_pixel_blackhole(render->bandaid, render->x, renderer_y,
                    render->light_value);
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

static void         draw_object(
        t_env *e, 
		const t_render *render,
		const t_collision *collision)
{
    double		x;
    double		y;
    Uint32		i;
    SDL_Surface *surface;
    t_u_range		range;
    double dist_ratio;

	if (collision->type != ct_object)
		return;
	surface = collision->d.object->sprite;
    x = get_distance_between_points(collision->inters.x,
            collision->inters.y, collision->object_segment.x1,
            collision->object_segment.y1)
            * surface->w / collision->d.object->horizontal_size;
    while (x > surface->w)
        x -= surface->w;
    dist_ratio = e->op.ratio / collision->distance;
    range = wall_range(dist_ratio, render->vision_height, render->win_h);
	i = range.start - 1;
	while (++i < range.end)
	{
        y = fabs((i - render->vision_height + dist_ratio / 2)
        * surface->h / dist_ratio) / collision->d.object->vertical_size
        + surface->h / collision->d.object->vertical_size
        * (collision->d.object->z + collision->d.object->vertical_size - 1);
        if (y >= surface->h || y < 0)
            continue;
        put_pixel_blackhole(e, render->x, i,
                get_pixel(surface, (Uint32)x, (Uint32)y, e_false));
	}
}

static void			draw_wall_object(
        t_env *e,
		const t_render *render,
		const t_collision *collision,
        t_wall_object	*wall_object)
{
    double		x;
    double		y;
    Uint32		i;
    SDL_Surface *surface;
    double dist_ratio;
    t_u_range range;

	surface = wall_object->texture;
    x = (get_distance_between_points(collision->inters.x,
            collision->inters.y, collision->d.wall->segment.x1,
            collision->d.wall->segment.y1) * surface->w);
    if (x >= (wall_object->offset_on_wall + wall_object->size) * surface->w
            || x < wall_object->offset_on_wall * surface->w)
        return;
    x -= (wall_object->offset_on_wall * surface->w);
    x = x / wall_object->size;
    dist_ratio = e->op.ratio / collision->distance;
    range = wall_range(dist_ratio, render->vision_height, render->win_h);
	i = range.start - 1;
	while (++i < range.end)
	{
        y = fabs((i - render->vision_height + dist_ratio / 2)
        * surface->h / dist_ratio) / wall_object->size
        + surface->h / wall_object->size
        * (wall_object->z + wall_object->size - 1);
        if (y >= surface->h || y < 0)
            continue;
        put_pixel_blackhole(e, render->x, i,
                get_pixel(surface, (Uint32)x, (Uint32)y, e_false));
	}
}

static void	draw_pickable(t_env *e, t_render *r, t_collision *collision)
{
    Uint32		x;
    int			y;
    Uint32		i;
    SDL_Surface *surface;
    t_u_range	range;
    double 		dist_ratio;

    if (collision->type != ct_pickable)
        return;
    surface = collision->d.pickable->object->sprite;
    x = (Uint32)(get_distance_between_points(collision->inters.x,
                                             collision->inters.y, collision->object_segment.x1,
                                             collision->object_segment.y1)
                 * surface->w / collision->d.pickable->object->horizontal_size) % surface->w;
    dist_ratio = e->op.ratio / collision->distance;
    range = wall_range(dist_ratio, r->vision_height, r->win_h);
    i = range.start - 1;
    while (++i < range.end)
    {
        y = (Uint32)(fabs(((i - r->vision_height + dist_ratio / 2)
                           * surface->h / dist_ratio))) / collision->d.pickable->object->vertical_size
            + surface->h / collision->d.enemy->object->vertical_size
              * (collision->d.pickable->object->z + collision->d.pickable->object->vertical_size - 1);
        if (y >= surface->h || y < 0)
            continue;
        put_pixel_alpha(e->doom.surface, r->x, i,
                            get_pixel(surface, x, y, e_false));
    }
}

static void	draw_enemy(t_env *e, t_render *r, t_collision *collision)
{
	Uint32		x;
	int			y;
	Uint32		i;
	SDL_Surface *surface;
	t_u_range	range;
	double 		dist_ratio;

	if (collision->type != ct_enemy)
		return;
	surface = collision->d.enemy->object->sprite;
	x = (Uint32)(get_distance_between_points(collision->inters.x,
											 collision->inters.y, collision->object_segment.x1,
											 collision->object_segment.y1)
				 * surface->w / collision->d.enemy->object->horizontal_size) % surface->w;
	dist_ratio = e->op.ratio / collision->distance;
	range = wall_range(dist_ratio, r->vision_height, r->win_h);
	i = range.start - 1;
	while (++i < range.end)
	{
		y = (Uint32)(fabs(((i - r->vision_height + dist_ratio / 2)
						   * surface->h / dist_ratio))) / collision->d.enemy->object->vertical_size
			+ surface->h / collision->d.enemy->object->vertical_size
			  * (collision->d.enemy->object->z + collision->d.enemy->object->vertical_size - 1);
		if (y >= surface->h || y < 0)
			continue;
        if (collision->d.enemy->type == et_boss)
            put_pixel_alpha(e->doom.surface, r->x, i,
						get_pixel(surface, x, y, e_false));
        else
            put_pixel_blackhole(e, r->x, i,
						get_pixel(surface, x, y, e_false));
	}
}

static void         draw_wall(
        t_env *e,
		const t_render *render,
		const t_collision *collision,
		const t_u_range range)
{
    Uint32		x;
    Uint32		y;
    Uint32		i;
    SDL_Surface *wall_text;

	if (collision->d.wall->type != e_wall)
		return;
	wall_text = collision->d.wall->texture;
	x = (Uint32)(get_distance_between_points(collision->inters.x,
	        collision->inters.y, collision->d.wall->segment.x1,
	        collision->d.wall->segment.y1) * wall_text->w) % wall_text->w;
	i = range.start;
	while (i < range.end)
	{
        y = (Uint32)(fabs(((i - (render->vision_height) + render->wall_height / 2)
        		* wall_text->h / render->wall_height))) % wall_text->h;
        put_pixel_blackhole(render->bandaid, render->x, i,
        		get_pixel(wall_text, x, y, e_true));
        if (render->lights)
        	put_pixel_blackhole(e, render->x, i, render->light_value);
		i++;
	}
    if (collision->d.wall->wall_object)
        draw_wall_object(e, render, collision, collision->d.wall->wall_object);
    if (collision->d.wall->lever)
        draw_wall_object(e, render, collision, collision->d.wall->lever->wall_object);
}

static t_render	fill_render_struct(t_env *e, Uint32 renderer_x)
{
	t_render render;

    render.bandaid = e;
	render.surface = e->doom.surface;
	render.x = renderer_x;
	render.vision_height = e->p.vision_height + e->p.jump.height;
	render.heading = e->p.heading;
	render.p_pos = e->p.pos;
	render.win_h = e->op.win_h;
	render.lights = e->op.lights;
	if (e->map->daytime)
		render.sky = e->map->daysky;
	else
		render.sky = e->map->nightsky;
	return (render);
}

void         draw_transparent_wall(
        t_env *e,
        const t_render *render,
        const t_collision *collision,
        const t_u_range range)
{
    double		x;
    Uint32		y;
    Uint32		i;
    SDL_Surface *wall_text;

    if (collision->d.wall->type != e_transparent_wall)
        return;
    if (collision->d.wall->to_infinity)
        skybox(render, range);
    wall_text = collision->d.wall->texture;
    x = get_distance_between_points(collision->inters.x,
            collision->inters.y, collision->d.wall->segment.x1,
            collision->d.wall->segment.y1);
    if (x < collision->d.wall->wall_offset)
        return;
    x = (Uint32)((x - collision->d.wall->wall_offset) * wall_text->w)
        % wall_text->w;
    i = range.start;
    while (i < range.end)
    {
        y = (Uint32)(fabs(((i - (render->vision_height) + render->wall_height / 2)
                           * wall_text->h / render->wall_height))) % wall_text->h;
        put_pixel_blackhole(e, render->x, i,
                get_pixel(wall_text, x, y, e_false));
        i++;
    }
}

static void	draw_transparents(t_env *e, t_render *r, t_collisions *node)
{
    if (!node)
        return;
    draw_transparents(e, r, node->next);
    if (node->item.type == ct_object)
        draw_object(e, r, &node->item);
    else if (node->item.type == ct_enemy)
    	draw_enemy(e, r, &node->item);
    else if (node->item.type == ct_pickable)
        draw_pickable(e, r, &node->item);
    else if (node->item.d.wall->type == e_transparent_wall)
    {
        r->wall_height =
                e->op.ratio / node->item.distance;
        draw_transparent_wall(e, r, &node->item, wall_range(r->wall_height, r->vision_height, r->win_h));
    }
}

static void	draw_walls(t_env *e, t_render *r, t_collisions *node)
{
	t_u_range		range;
	t_u_range		prev_range;
	t_u_range		ceil_or_floor_range;
	t_sector		*current_sector;

	current_sector = e->p.current_sector;
	prev_range.start = 0;
	prev_range.end = e->op.win_h;
	while (node)
	{
		r->light_value = current_sector->light;
		r->wall_height =
                e->op.ratio / node->item.distance;
        if (node->item.type == ct_wall)
        {
            range = wall_range(r->wall_height, r->vision_height, r->win_h);
            draw_wall(e, r, &node->item, range);
            ceil_or_floor_range.start = range.end;
            ceil_or_floor_range.end = prev_range.end;
            draw_flat(r, &node->item, ceil_or_floor_range, current_sector->floor);
            ceil_or_floor_range.start = prev_range.start;
            ceil_or_floor_range.end = range.start;
            draw_ceil(r, &node->item, ceil_or_floor_range, current_sector);
            current_sector = get_next_sector_addr(current_sector, node->item.d.wall);
            prev_range = range;
        }
		node = node->next;
	}
}

void		draw(t_env *e, t_collisions *node, Uint32 renderer_x)
{
	t_render		r;

	r = fill_render_struct(e, renderer_x);
    draw_walls(e, &r, node);
    draw_transparents(e, &r, node);
}
