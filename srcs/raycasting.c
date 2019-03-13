/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfatton <lfatton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 01:10:34 by lfatton           #+#    #+#             */
/*   Updated: 2019/03/08 18:44:21 by lfatton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

double	get_dist_intersection(t_env *e, t_coords inters)
{
	double		x_diff;
	double		y_diff;

	x_diff = ft_dabs(e->p->pos.x - inters.x);
	y_diff = ft_dabs(e->p->pos.y - inters.y);

	return sqrt(x_diff * x_diff + y_diff * y_diff);
}

void	raycasting(t_env *e)
{
	t_coords    inters;
	t_vector	ray;
	t_segment	ray_seg;
	Uint32		i;
	double		iterating_angle;
	double 		smallest_distance;
	double		distance;
	double		ray_angle;

	e->col = 0;
	while (e->col < WIN_W)
	{
		iterating_angle = atan(((e->col / HALF_W - 1) / TAN_HALF_FOV) * TAN_HALF_FOV);
		ray_angle = e->p->heading + iterating_angle;
		while (ray_angle >= CIRCLE)
			ray_angle -= CIRCLE;
		while (ray_angle < 0)
			ray_angle += CIRCLE;

		ray = create_vector(cos(ray_angle), -sin(ray_angle));
		scalar_multiply(&ray, HORIZON);
		ray_seg = create_segment_from_position_and_vector(
				e->p->pos.x,
				e->p->pos.y,
				&ray);

		smallest_distance = HORIZON;
		i = 0;
		while (i < e->seg_count)
		{
            if (segments_intersect(&ray_seg, &e->walls[i], &inters))
            {
                distance = get_dist_intersection(e, inters);
                if (distance < smallest_distance)
				{
					smallest_distance = distance;
					e->wall_id = i;
				}
            }
			i++;
		}
		draw(e, ray_angle, smallest_distance);
		e->col++;
	}
}
