/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfatton <lfatton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 01:10:34 by lfatton           #+#    #+#             */
/*   Updated: 2019/03/13 11:58:05 by lfatton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static enum		e_bool segments_intersect(t_segment *a, t_segment *b, t_coords *inters)
{
	t_coords		delta_a;
	t_coords		delta_b;
	double			s;
	double			t;

	delta_a.x = a->x2 - a->x1;
	delta_a.y = a->y2 - a->y1;
	delta_b.x = b->x2 - b->x1;
	delta_b.y = b->y2 - b->y1;
	s = (-delta_a.y * (a->x1 - b->x1) + delta_a.x * (a->y1 - b->y1)) / (-delta_b.x * delta_a.y + delta_a.x * delta_b.y);
	t = (delta_b.x * (a->y1 - b->y1) - delta_b.y * (a->x1 - b->x1)) / (-delta_b.x * delta_a.y + delta_a.x * delta_b.y);
	if (s >= 0 && s <= 1 && t >= 0 && t <= 1) {
		inters->x = a->x1 + (t * delta_a.x);
		inters->y = a->y1 + (t * delta_a.y);
		return (t_true);
	}

	return (t_false);
}

static double	get_dist_intersection(t_player *p, t_coords inters)
{
	double		x_diff;
	double		y_diff;

	x_diff = ft_dabs(p->pos.x - inters.x);
	y_diff = ft_dabs(p->pos.y - inters.y);

	return sqrt(x_diff * x_diff + y_diff * y_diff);
}

double			check_collision(t_sector *sector, t_player *p, t_vector *vector)
{
	t_coords		inters;
	t_segment	seg_from_vect;
	Uint32		i;
	double		distance;
	double		smallest_distance;

	scalar_multiply(vector, HORIZON);
	seg_from_vect = create_segment_from_position_and_vector(p->pos.x, p->pos.y, vector);
	smallest_distance = HORIZON;
	i = 0;
	while (i < sector->seg_count)
	{
		if (segments_intersect(&seg_from_vect, &sector->walls[i], &inters))
		{
			distance = get_dist_intersection(p, inters);
			if (distance < smallest_distance)
			{
				smallest_distance = distance;
				sector->wall_id = i;
			}
		}
		i++;
	}
	return (smallest_distance);
}

void			raycasting(t_env *e)
{
	t_vector	ray;
	double		iterating_angle;
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
		draw(e, ray_angle, check_collision(e->sector, e->p, &ray));
		e->col++;
	}
}
