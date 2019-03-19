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

#include "utils.h"
#include "e_bool.h"
#include "libft.h"
#include <math.h>
#include "collision.h"
#include "default.h"
#include "doom.h"
#include "engine.h"

static enum e_bool segments_intersect(t_segment *a, t_segment *b, t_coords *inters)
{
    t_coords delta_a;
    t_coords delta_b;
    double s;
    double t;

    delta_a.x = a->x2 - a->x1;
    delta_a.y = a->y2 - a->y1;
    delta_b.x = b->x2 - b->x1;
    delta_b.y = b->y2 - b->y1;
    s = (-delta_a.y * (a->x1 - b->x1) + delta_a.x * (a->y1 - b->y1)) / (-delta_b.x * delta_a.y + delta_a.x * delta_b.y);
    t = (delta_b.x * (a->y1 - b->y1) - delta_b.y * (a->x1 - b->x1)) / (-delta_b.x * delta_a.y + delta_a.x * delta_b.y);
    if (s >= 0 && s <= 1 && t >= 0 && t <= 1)
    {
        inters->x = a->x1 + (t * delta_a.x);
        inters->y = a->y1 + (t * delta_a.y);
        return (t_true);
    }

    return (t_false);
}

static double get_dist_intersection(double x1, double y1, double x2, double y2)
{
    t_coords delta;

    delta.x = ft_dabs(x1 - x2);
    delta.y = ft_dabs(y1 - y2);

    return sqrt(delta.x * delta.x + delta.y * delta.y);
}


t_collision check_collision(t_sector *sector, t_segment *seg)
{
	t_collision	collision;
	double		temp_distance;
	int		    i;
	t_coords	inters;

	collision.distance = HORIZON;
	i = 0;
	while (i < sector->walls->count)
	{
		if (segments_intersect(seg, &sector->walls->items[i].segment, &inters))
		{
			temp_distance = get_dist_intersection(seg->x1, seg->y1,
					inters.x, inters.y);
			if (temp_distance < collision.distance)
			{
				collision.inters.x = inters.x;
				collision.inters.y = inters.y;
				collision.distance = temp_distance;
				collision.wall = &sector->walls->items[i];
			}
		}
		i++;
	}
	return (collision);
}

void			raycasting(t_env *e, t_map *map)
{
	t_vector	ray_vect;
	t_segment	ray_seg;
	double		ray_angle;
    Uint32      renderer_x;
    t_sector sector;

    sector = map->sectors->items[0];

    renderer_x = 0;
    while (renderer_x < WIN_W)
    {
        ray_angle = e->p->heading + atan(
                (renderer_x / HALF_W - 1) * TAN_HALF_FOV);
        while (ray_angle >= CIRCLE)
            ray_angle -= CIRCLE;
        while (ray_angle < 0)
            ray_angle += CIRCLE;

		ray_vect = create_vector(cos(ray_angle), -sin(ray_angle));
		scalar_multiply(&ray_vect, HORIZON);
		ray_seg = create_segment_from_position_and_vector(
				e->p->pos.x,
				e->p->pos.y,
				&ray_vect);
		draw(e, ray_angle, check_collision(&sector, &ray_seg), renderer_x);
		renderer_x++;
	}
}
