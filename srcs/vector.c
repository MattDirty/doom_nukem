/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtorsell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/20 01:39:36 by mtorsell          #+#    #+#             */
/*   Updated: 2019/04/20 01:39:39 by mtorsell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include <math.h>

t_segment	get_segment_from_vector(t_vector *vector)
{
	t_segment segment;

	segment.x1 = 0;
	segment.y1 = 0;
	segment.x2 = 0 + vector->x;
	segment.y2 = 0 + vector->y;
	return (segment);
}

void		rotate_vector(t_vector *vector, double rad)
{
	double swap_x;

	swap_x = vector->x * cos(rad) - vector->y * sin(rad);
	vector->y = vector->x * sin(rad) + vector->y * cos(rad);
	vector->x = swap_x;
}

double		dot_product(t_vector *vector1, t_vector *vector2)
{
	return (vector1->x * vector2->x + vector1->y * vector2->y);
}

double		get_vector_length(t_vector *vector)
{
	return (sqrt(vector->x * vector->x + vector->y * vector->y));
}

void		change_vector_magnitude(t_vector *vector, double new_magnitude)
{
	double old_magnitude;

	old_magnitude = get_vector_length(vector);
	vector->x = vector->x * fabs(new_magnitude / old_magnitude);
	vector->y = vector->y * fabs(new_magnitude / old_magnitude);
}
