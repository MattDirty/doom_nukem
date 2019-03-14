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

static double	get_dist_intersection(t_coords start, t_coords inters)
{
	t_coords    delta;

	delta.x = ft_dabs(start.x - inters.x);
	delta.y = ft_dabs(start.y - inters.y);

	return sqrt(delta.x * delta.x + delta.y * delta.y);
}


double			check_collision(t_sector *sector, t_segment *seg)
{
	t_coords	inters;
	t_coords	start;
	Uint32		i;
	double		distance;
	double		smallest_distance;

	smallest_distance = HORIZON;
	i = 0;
	start.x = seg->x1;
	start.y = seg->y1;
	while (i < sector->seg_count)
	{
		if (segments_intersect(seg, &sector->walls[i], &inters))
		{
			distance = get_dist_intersection(start, inters);
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
	t_vector	ray_vect;
	t_segment	ray_seg;
	double		iterating_angle;
	double		ray_angle;
    Uint32      renderer_x;

	renderer_x = 0;
	while (renderer_x < WIN_W)
	{
		iterating_angle = atan(((renderer_x / HALF_W - 1) / TAN_HALF_FOV) * TAN_HALF_FOV);
		ray_angle = e->p->heading + iterating_angle;
		while (ray_angle >= CIRCLE)
			ray_angle -= CIRCLE;
		while (ray_angle < 0)
			ray_angle += CIRCLE;

		ray_vect = create_vector(cos(ray_angle), -sin(ray_angle));
		scalar_multiply(&ray_vect, HORIZON);
		ray_seg = create_segment_from_position_and_vector(e->p->pos.x, e->p->pos.y, &ray_vect);
		draw(e, ray_angle, check_collision(e->sector, &ray_seg), renderer_x);
		renderer_x++;
	}
}
