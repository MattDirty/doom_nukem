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

void			draw_enemy(t_env *e, t_render *r, t_collision *collision)
{
	Uint32		x;
	int			y;
	Uint32		i;
	SDL_Surface	*surface;
	t_u_range	range;
	double		dist_ratio;

	if (collision->type != ct_enemy)
		return ;
	surface = collision->d.enemy->object->sprite;
	x = (Uint32)(get_distance_between_points(collision->inters.x,
			collision->inters.y, collision->object_segment.x1,
			collision->object_segment.y1) * surface->w
			/ collision->d.enemy->object->horizontal_size) % surface->w;
	dist_ratio = e->op.ratio / collision->distance;
	range = wall_range(dist_ratio, r->vision_height, r->win_h);
	i = range.start - 1;
	while (++i < range.end)
	{
		y = (Uint32)(fabs(((i - r->vision_height + dist_ratio / 2)
					* surface->h / dist_ratio))) /
					collision->d.enemy->object->vertical_size + surface->h
					/ collision->d.enemy->object->vertical_size
					* (collision->d.enemy->object->z +
					collision->d.enemy->object->vertical_size - 1);
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

static t_render	fill_render_struct(t_env *e, Uint32 renderer_x)
{
	t_render	render;

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

void			draw(t_env *e, t_collisions *node, Uint32 renderer_x)
{
	t_render r;

	r = fill_render_struct(e, renderer_x);
	draw_walls(e, &r, node);
	draw_transparents(e, &r, node);
}
