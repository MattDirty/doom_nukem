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
#include "player.h"
#include "default.h"
#include "doom.h"
#include "player.h"
#include "render.h"

enum e_bool segments_intersect(t_segment *a, t_segment *b, t_coords *inters)
{
    t_coords delta_a;
    t_coords delta_b;
    double s;
    double t;

    delta_a.x = a->x2 - a->x1;
    delta_a.y = a->y2 - a->y1;
    delta_b.x = b->x2 - b->x1;
    delta_b.y = b->y2 - b->y1;
    s = (-delta_a.y * (a->x1 - b->x1) + delta_a.x * (a->y1 - b->y1))
            / (-delta_b.x * delta_a.y + delta_a.x * delta_b.y);
    t = (delta_b.x * (a->y1 - b->y1) - delta_b.y * (a->x1 - b->x1))
            / (-delta_b.x * delta_a.y + delta_a.x * delta_b.y);
    if (s >= 0 && s <= 1 && t >= 0 && t <= 1)
    {
        inters->x = a->x1 + (t * delta_a.x);
        inters->y = a->y1 + (t * delta_a.y);
        return (t_true);
    }
    return (t_false);
}

t_sector	*get_next_sector_addr(t_sector *current, t_wall *wall)
{
	if (wall->pointer.sector.sector1 == current)
		return (wall->pointer.sector.sector2);
	else if (wall->pointer.sector.sector2 == current)
		return (wall->pointer.sector.sector1);
	return (NULL);
}

void			raycasting(t_env *e)
{
	t_ray		ray;
    Uint32      renderer_x;
    t_collision	*collision;
    Uint32      collisions_number;

    renderer_x = 0;
    collision = NULL;
    while (renderer_x < e->op.win_w)
    {
        clamp_player_values(&e->p, e->op);
        ray.angle = e->p.heading + atan(
                (renderer_x / e->op.half_w - 1) * e->op.tan_half_fov);
		ray.vect = create_vector(cos(ray.angle), -sin(ray.angle));
		change_vector_magnitude(&ray.vect, HORIZON);
		ray.seg = create_segment_from_position_and_vector(
				e->p.pos.x,
				e->p.pos.y,
				&ray.vect);
		if ((collisions_number = check_collision(e->p.current_sector, &ray.seg, &collision)))
		{
			collision[collisions_number - 1].distance *= cos(e->p.heading - ray.angle);
			draw(e, collision[collisions_number - 1], renderer_x, ray);
		}
		renderer_x++;
	}
}
