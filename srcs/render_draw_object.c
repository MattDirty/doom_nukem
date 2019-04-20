/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_draw_object.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtorsell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/20 15:49:51 by mtorsell          #+#    #+#             */
/*   Updated: 2019/04/20 15:49:52 by mtorsell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "collision.h"
#include "doom.h"
#include "default.h"
#include "render.h"
#include "render_blackhole.h"
#include "surface_manipulation.h"
#include <math.h>

static double	calculate_y(Uint32 i, const t_render *r, double dist_ratio,
					const t_collision *col)
{
	SDL_Surface	*surface;

	surface = col->d.object->sprite;
	return (fabs((i - r->vision_height + dist_ratio / 2) * surface->h
				/ dist_ratio) / col->d.object->vertical_size
			+ surface->h / col->d.object->vertical_size
			* (col->d.object->z + col->d.object->vertical_size - 1));
}

void			draw_object(t_env *e, const t_render *r,
							const t_collision *col)
{
	t_coords	inc;
	Uint32		i;
	SDL_Surface	*surface;
	t_u_range	range;
	double		dist_ratio;

	surface = col->d.object->sprite;
	inc.x = get_distance_between_points(col->inters.x, col->inters.y,
				col->object_segment.x1, col->object_segment.y1) * surface->w
			/ col->d.object->horizontal_size;
	while (inc.x > surface->w)
		inc.x -= surface->w;
	dist_ratio = e->op.ratio / col->distance;
	range = wall_range(dist_ratio, r->vision_height, r->win_h);
	i = range.start - 1;
	while (++i < range.end)
	{
		inc.y = calculate_y(i, r, dist_ratio, col);
		if (inc.y >= surface->h || inc.y < 0)
			continue;
		put_pixel_blackhole(e, r->x, i, get_pixel(surface, (Uint32)inc.x,
				(Uint32)inc.y, e_false));
	}
}
