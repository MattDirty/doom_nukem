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

void	get_dist_intersection(t_env *e, t_coords inters)
{
	double		x_diff;
	double		y_diff;
	double		tmp;
	
	x_diff = ft_dabs(e->p->pos.x - inters.x);
	y_diff = ft_dabs(e->p->pos.y - inters.y);
	if (x_diff > y_diff)
		tmp = ft_dabs(x_diff / cos(e->r->ang));
	else
		tmp = ft_dabs(y_diff / sin(e->r->ang));
	//tmp = (sqrt(ft_sq(x_diff) + ft_sq((y_diff)))); //dist mit sqrt instead of sin or cos of the angle
	if (tmp < e->r->dist)
		e->r->dist = tmp;
}

void	raycasting(t_env *e)
{
	t_coords    inters;
	t_vector	ray;
	t_segment	ray_seg;
	Uint32		i;
	double      tmp; // debug

	e->col = 0;
	while (e->col < WIN_W)
	{
		e->r->ang =  e->p->vis - (ft_degtorad(FOV) - atan((HALF_W - e->col) / HALF_W));
		while (e->r->ang >= CIRCLE)
			e->r->ang -= CIRCLE;
		while (e->r->ang < 0)
			e->r->ang += CIRCLE;
		ray = create_vector(cos(e->r->ang), (sin(e->r->ang)));
		ray_seg = get_segment_from_vector(&ray);
		move_segment_at (&ray_seg, e->p->pos.x, e->p->pos.y);
		change_segment_length(&ray_seg, HORIZON);
		e->r->dist = HORIZON;
		i = 0;
		while (i < e->seg_count)
		{
            if (segments_intersect(&ray_seg, &e->walls[i], &inters))
            {
                tmp = e->r->dist;
                get_dist_intersection(e, inters);
                if (tmp != e->r->dist)
                {
                    tmp = e->r->dist;
                    e->wall_id = i;
                }
            }
			i++;
		}
		draw(e);
		e->col++;
	}
}
