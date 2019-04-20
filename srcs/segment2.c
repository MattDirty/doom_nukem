/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   segment2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtorsell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/20 03:48:42 by mtorsell          #+#    #+#             */
/*   Updated: 2019/04/20 03:48:43 by mtorsell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "doom.h"
#include <math.h>
#include <unistd.h>

enum e_bool	segments_share_node(t_segment *s1, t_segment *s2)
{
	return ((fabs(s1->x1 - s2->x1) < 0.001 && fabs(s1->y1 - s2->y1) < 0.001)
		|| (fabs(s1->x2 - s2->x1) < 0.001 && fabs(s1->y2 - s2->y1) < 0.001)
		|| (fabs(s1->x2 - s2->x2) < 0.001 && fabs(s1->y2 - s2->y2) < 0.001)
		|| (fabs(s1->x1 - s2->x2) < 0.001 && fabs(s1->y1 - s2->y2) < 0.001));
}

enum e_bool	segments_intersect(t_segment *a, t_segment *b, t_coords *inters)
{
	t_coords	delta_a;
	t_coords	delta_b;
	double		s;
	double		t;

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
		return (e_true);
	}
	return (e_false);
}

void		move_segment_at(t_segment *segment, double x, double y)
{
	t_coords swap;

	swap.x = segment->x1;
	swap.y = segment->y1;
	segment->x1 = x;
	segment->y1 = y;
	segment->x2 -= swap.x - x;
	segment->y2 -= swap.y - y;
}

t_vector	get_vector_from_segment(t_segment *segment)
{
	t_vector vector;

	vector.x = segment->x2 - segment->x1;
	vector.y = segment->y2 - segment->y1;
	return (vector);
}
