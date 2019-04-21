/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall_object.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtorsell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/20 14:10:56 by mtorsell          #+#    #+#             */
/*   Updated: 2019/04/20 14:10:57 by mtorsell         ###   ########.fr       */
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
			const t_collision *collision, t_wall_object *w_o)
{
	t_coords	c;
	Uint32		i;
	double		ratio;
	t_u_range	range;

	c.x = (get_distance_between_points(collision->inters.x, collision->inters.y,
			collision->d.wall->segment.x1, collision->d.wall->segment.y1)
		* w_o->texture->w);
	if (c.x >= (w_o->offset_on_wall + w_o->size) * w_o->texture->w
		|| c.x < w_o->offset_on_wall * w_o->texture->w)
		return ;
	c.x = (c.x - w_o->offset_on_wall * w_o->texture->w) / w_o->size;
	ratio = e->op.ratio / collision->distance;
	range = wall_range(ratio, render->vision_height, render->win_h);
	i = range.start - 1;
	while (++i < range.end)
	{
		c.y = fabs((i - render->vision_height + ratio / 2) * w_o->texture->h
				/ ratio) / w_o->size + w_o->texture->h
						/ w_o->size * (w_o->z + w_o->size - 1);
		if (c.y >= w_o->texture->h || c.y < 0)
			continue ;
		put_pixel_blackhole(e, render->x, i,
				get_pixel(w_o->texture, (Uint32)c.x, (Uint32)c.y, e_false));
	}
}
