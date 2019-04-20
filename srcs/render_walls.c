/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_walls.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfatton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/20 09:40:39 by lfatton           #+#    #+#             */
/*   Updated: 2019/04/20 09:40:41 by lfatton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "collision.h"
#include "doom.h"
#include "default.h"
#include "render.h"
#include "render_blackhole.h"
#include "surface_manipulation.h"
#include <math.h>

void	draw_wall_object(t_env *e, const t_render *render,
			const t_collision *collision, t_wall_object *wall_object)
{
	double		x;
	double		y;
	Uint32		i;
	SDL_Surface	*surface;
	double		dist_ratio;
	t_u_range	range;

	surface = wall_object->texture;
	x = (get_distance_between_points(collision->inters.x, collision->inters.y,
		collision->d.wall->segment.x1, collision->d.wall->segment.y1)
		* surface->w);
	if (x >= (wall_object->offset_on_wall + wall_object->size) * surface->w
		|| x < wall_object->offset_on_wall * surface->w)
		return ;
	x -= (wall_object->offset_on_wall * surface->w);
	x = x / wall_object->size;
	dist_ratio = e->op.ratio / collision->distance;
	range = wall_range(dist_ratio, render->vision_height, render->win_h);
	i = range.start - 1;
	while (++i < range.end)
	{
		y = fabs((i - render->vision_height + dist_ratio / 2) * surface->h
			/ dist_ratio) / wall_object->size + surface->h / wall_object->size
			* (wall_object->z + wall_object->size - 1);
		if (y >= surface->h || y < 0)
			continue;
		put_pixel_blackhole(e, render->x, i,
			get_pixel(surface, (Uint32)x, (Uint32)y, e_false));
	}
}

void	draw_transparent_wall(t_env *e, const t_render *render,
			const t_collision *collision, const t_u_range range)
{
	double		x;
	Uint32		y;
	Uint32		i;
	SDL_Surface	*wall_text;

	if (collision->d.wall->type != e_transparent_wall)
		return ;
	if (collision->d.wall->to_infinity)
		skybox(render, range);
	wall_text = collision->d.wall->texture;
	x = get_distance_between_points(collision->inters.x, collision->inters.y,
		collision->d.wall->segment.x1, collision->d.wall->segment.y1);
	if (x < collision->d.wall->wall_offset)
		return ;
	x = (Uint32)((x - collision->d.wall->wall_offset) * wall_text->w)
		% wall_text->w;
	i = range.start;
	while (i < range.end)
	{
		y = (Uint32)(fabs(((i - (render->vision_height) + render->wall_height
			/ 2) * wall_text->h / render->wall_height))) % wall_text->h;
		put_pixel_blackhole(e, render->x, i,
			get_pixel(wall_text, x, y, e_false));
		i++;
	}
}

void	draw_transparents(t_env *e, t_render *r, t_collisions *node)
{
	if (!node)
		return ;
	draw_transparents(e, r, node->next);
	if (node->item.type == ct_object)
		draw_object(e, r, &node->item);
	else if (node->item.type == ct_enemy)
		draw_enemy(e, r, &node->item);
	else if (node->item.type == ct_pickable)
		draw_pickable(e, r, &node->item);
	else if (node->item.d.wall->type == e_transparent_wall)
	{
		r->wall_height = e->op.ratio / node->item.distance;
		draw_transparent_wall(e, r, &node->item, wall_range(r->wall_height,
			r->vision_height, r->win_h));
	}
}

void	draw_wall(t_env *e, const t_render *render,
			const t_collision *collision, const t_u_range range)
{
	Uint32		x;
	Uint32		y;
	Uint32		i;
	SDL_Surface	*wall_text;

	if (collision->d.wall->type != e_wall)
		return ;
	wall_text = collision->d.wall->texture;
	x = (Uint32)(get_distance_between_points(collision->inters.x,
				collision->inters.y, collision->d.wall->segment.x1,
				collision->d.wall->segment.y1) * wall_text->w) % wall_text->w;
	i = range.start;
	while (i < range.end)
	{
		y = (Uint32)(fabs(((i - (render->vision_height) + render->wall_height
					/ 2) * wall_text->h / render->wall_height))) % wall_text->h;
		put_pixel_blackhole(render->bandaid, render->x, i,
			get_pixel(wall_text, x, y, e_true));
		if (render->lights)
			put_pixel_blackhole(e, render->x, i, render->light_value);
		i++;
	}
	if (collision->d.wall->wall_object)
		draw_wall_object(e, render, collision, collision->d.wall->wall_object);
	if (collision->d.wall->lever)
		draw_wall_object(e, render, collision,
			collision->d.wall->lever->wall_object);
}

void	draw_walls(t_env *e, t_render *r, t_collisions *node)
{
	t_u_range	range;
	t_u_range	prev_range;
	t_u_range	ceil_or_floor_range;
	t_sector	*current_sector;

	current_sector = e->p.current_sector;
	prev_range.start = 0;
	prev_range.end = e->op.win_h;
	while (node)
	{
		r->light_value = current_sector->light;
		r->wall_height = e->op.ratio / node->item.distance;
		if (node->item.type == ct_wall)
		{
			range = wall_range(r->wall_height, r->vision_height, r->win_h);
			draw_wall(e, r, &node->item, range);
			ceil_or_floor_range.start = range.end;
			ceil_or_floor_range.end = prev_range.end;
			draw_flat(r, &node->item, ceil_or_floor_range,
				current_sector->floor);
			ceil_or_floor_range.start = prev_range.start;
			ceil_or_floor_range.end = range.start;
			draw_ceil(r, &node->item, ceil_or_floor_range, current_sector);
			current_sector = get_next_sector_addr(current_sector,
				node->item.d.wall);
			prev_range = range;
		}
		node = node->next;
	}
}
