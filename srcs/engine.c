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

#include <stdio.h>
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

t_sector	*get_next_sector_addr(t_sector *current, t_wall *wall)
{
    if (wall->to_infinity)
        return (NULL);
	if (wall->links.sector1 == current)
		return (wall->links.sector2);
	else if (wall->links.sector2 == current)
		return (wall->links.sector1);
	return (NULL);
}

void			raycasting(t_env *e)
{
	t_ray			ray;
    Uint32			renderer_x;
    t_collisions	*collisions;
    t_collisions	*ptr;

    renderer_x = -1;
	clamp_player_values(&e->p, e->op);
    while (++renderer_x < e->op.win_w)
    {
        ray.angle = e->p.heading + atan(
                (renderer_x / e->op.half_w - 1) * e->op.tan_half_fov);
		ray.vect = create_vector(cos(ray.angle), -sin(ray.angle));
		change_vector_magnitude(&ray.vect, HORIZON);
		ray.seg = create_segment_from_position_and_vector(e->p.pos.x,
		        e->p.pos.y, &ray.vect);
		find_ray_collisions(e->p.current_sector, &ray.seg, &collisions);
        if (!collisions)
            continue;
		ptr = collisions;
		while (ptr)
		{
			ptr->item.distance *= cos(e->p.heading - ray.angle);
			ptr = ptr->next;
		}
		draw(e, collisions, renderer_x);
		free_collisions(collisions);
	}
}
