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
	if (tmp < e->r->dist)
		e->r->dist = tmp;
}

void	raycasting(t_env *e)
{
        t_segment	*walls;
	t_segment	W1_seg;
        t_segment	W2_seg;
        t_segment	W3_seg;
        t_segment	W4_seg;
        t_coords        inters;
	t_vector	ray;
        t_segment	ray_seg;
	int		i;
	int		numsg;

        //SEGS FROM ORIGIN UPSIDE LEFT CORNER
	//W1_seg = create_segment(0, 3, 2, 5);
        //W2_seg = create_segment(2, 5, 4, 0);
        //W3_seg = create_segment(4, 0, 2, 0);
        //W4_seg = create_segment(2, 0, 0, 3);
        
        //SEGS FROM ORIGIN AT PLAYER
	W1_seg = create_segment(-2, -1, 3, 0);
        W2_seg = create_segment(3, 0, 2, 2);
        W3_seg = create_segment(2, 2, 0, 2);
        W4_seg = create_segment(0, 2, -2, -1);
	numsg = 4;
	if (!(walls = (t_segment*)malloc(sizeof(t_segment) * numsg)))
		error_doom("cannot allocate memory");
	walls[0] = W1_seg;
	walls[1] = W2_seg;
	walls[2] = W3_seg;
	walls[3] = W4_seg;

	e->col = 0;
	e->r->ang = e->p->vis + ft_degtorad(FOV / 2);
	while (e->col < WIN_W)
	{
		while (e->r->ang >= CIRCLE)
			e->r->ang -= CIRCLE;
		while (e->r->ang < 0)
			e->r->ang += CIRCLE;
		ray = create_vector_at(cos(e->r->ang), sin(e->r->ang), e->p->pos.x, e->p->pos.y);
		ray_seg = get_segment_from_vector(&ray);
		change_segment_length(&ray_seg, HORIZON);
		e->r->dist = HORIZON;
		i = 0;
		while (i < numsg)
		{
			if (get_line_intersection(&ray_seg, &walls[i], &inters))
				get_dist_intersection(e, inters);
			i++;
		}
		draw(e);
		e->r->ang -= DECR_ANG;
		e->col++;
	}
}
