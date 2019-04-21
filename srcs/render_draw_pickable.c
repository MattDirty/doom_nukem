/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_draw_pickable.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtorsell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/20 15:49:37 by mtorsell          #+#    #+#             */
/*   Updated: 2019/04/20 15:49:38 by mtorsell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "collision.h"
#include "doom.h"
#include "default.h"
#include "render.h"
#include "render_blackhole.h"
#include "surface_manipulation.h"
#include <math.h>

static Uint32	calculate_y(Uint32 i, const t_render *r, double dist_ratio,
					const t_collision *col)
{
	SDL_Surface	*surface;

	surface = col->d.pickable->object->sprite;
	return ((Uint32)(fabs(((i - r->vision_height + dist_ratio / 2)
				* surface->h / dist_ratio)))
		/ col->d.pickable->object->vertical_size + surface->h
		/ col->d.enemy->object->vertical_size
		* (col->d.pickable->object->z + col->d.pickable->object->vertical_size
			- 1));
}

void			draw_pickable(t_env *e, t_render *r, t_collision *col)
{
	t_i_coords	c;
	Uint32		i;
	SDL_Surface	*surface;
	t_u_range	range;
	double		dist_ratio;

	surface = col->d.pickable->object->sprite;
	c.x = (Uint32)(get_distance_between_points(col->inters.x,
			col->inters.y, col->object_segment.x1,
			col->object_segment.y1) * surface->w
			/ col->d.pickable->object->horizontal_size) % surface->w;
	dist_ratio = e->op.ratio / col->distance;
	range = wall_range(dist_ratio, r->vision_height, r->win_h);
	i = range.start - 1;
	while (++i < range.end)
	{
		c.y = calculate_y(i, r, dist_ratio, col);
		if (c.y >= surface->h || c.y < 0)
			continue;
		put_pixel_alpha(e->doom.surface, r->x, i,
						get_pixel(surface, c.x, c.y, e_false));
	}
}
