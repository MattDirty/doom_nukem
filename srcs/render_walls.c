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
			const t_collision *cl, const t_u_range range)
{
	t_coords	c;
	Uint32		i;
	SDL_Surface	*w_t;

	if (cl->d.wall->type != e_wall)
		return ;
	w_t = cl->d.wall->texture;
	c.x = (Uint32)(get_distance_between_points(cl->inters.x, cl->inters.y,
			cl->d.wall->segment.x1, cl->d.wall->segment.y1) * w_t->w) % w_t->w;
	i = range.start;
	while (i < range.end)
	{
		c.y = (Uint32)(fabs(((i - (render->vision_height) + render->wall_height
					/ 2) * w_t->h / render->wall_height))) % w_t->h;
		put_pixel_blackhole(render->bandaid, render->x, i,
			get_pixel(w_t, c.x, c.y, e_true));
		if (render->lights)
			put_pixel_blackhole(e, render->x, i, render->light_value);
		i++;
	}
	if (cl->d.wall->wall_object)
		draw_wall_object(e, render, cl, cl->d.wall->wall_object);
	if (cl->d.wall->lever)
		draw_wall_object(e, render, cl,
			cl->d.wall->lever->wall_object);
}

void	draw_walls(t_env *e, t_render *r, t_collisions *node)
{
	t_u_range	range;
	t_u_range	prev_range;
	t_u_range	ceil_or_floor_range;
	t_sector	*cur_sect;

	cur_sect = e->p.current_sector;
	prev_range = (t_u_range){0, e->op.win_h};
	while (node)
	{
		r->light_value = cur_sect->light;
		r->wall_height = e->op.ratio / node->item.distance;
		if (node->item.type == ct_wall)
		{
			range = wall_range(r->wall_height, r->vision_height, r->win_h);
			draw_wall(e, r, &node->item, range);
			ceil_or_floor_range = (t_u_range){range.end, prev_range.end};
			draw_flat(r, &node->item, ceil_or_floor_range, cur_sect->floor);
			ceil_or_floor_range = (t_u_range){prev_range.start, range.start};
			draw_ceil(r, &node->item, ceil_or_floor_range, cur_sect);
			cur_sect = get_next_sector_addr(cur_sect,
				node->item.d.wall);
			prev_range = range;
		}
		node = node->next;
	}
}
