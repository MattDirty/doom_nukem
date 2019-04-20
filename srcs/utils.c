/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badhont <badhont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 17:49:26 by mtorsell          #+#    #+#             */
/*   Updated: 2019/04/18 08:39:47 by badhont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <unistd.h>
#include <stdlib.h>
#include "e_bool.h"
#include "utils.h"
#include "doom.h"

enum e_bool	invert_bool(enum e_bool bool)
{
	if (bool)
		return (e_false);
	return (e_true);
}

void		normalize_vector(t_vector *vector)
{
	double l;

	l = get_vector_length(vector);
	vector->x /= l;
	vector->y /= l;
}

double		get_distance_between_points(double x1, double y1,
				double x2, double y2)
{
	return (sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2)));
}
