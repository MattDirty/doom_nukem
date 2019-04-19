/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtorsell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/20 01:41:55 by mtorsell          #+#    #+#             */
/*   Updated: 2019/04/20 01:41:57 by mtorsell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include <math.h>
#include <stdio.h>

double			get_rad_between_vectors(t_vector *vector1, t_vector *vector2)
{
	double len1;
	double len2;

	len1 = get_vector_length(vector1);
	len2 = get_vector_length(vector2);
	return (acos(dot_product(vector1, vector2) / (len1 * len2)));
}

void			add_vector_to_vector(t_vector *vector, t_vector vector2)
{
	vector->x += vector2.x;
	vector->y += vector2.y;
}

void			scalar_multiply(t_vector *vector, double scalar)
{
	vector->x *= scalar;
	vector->y *= scalar;
}

t_segment		create_segment_from_position_and_vector(
		double x,
		double y,
		t_vector *v)
{
	t_segment segment;

	segment.x1 = x;
	segment.y1 = y;
	segment.x2 = x + v->x;
	segment.y2 = y + v->y;
	return (segment);
}

t_vector		create_vector(double x, double y)
{
	t_vector new_vector;

	new_vector.x = x;
	new_vector.y = y;
	return (new_vector);
}
