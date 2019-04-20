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

int			is_close_to(t_coords target, t_coords pos, double distance)
{
	if ((fabs(pos.x - target.x) < distance)
		&& (fabs(pos.y - target.y) < distance))
		return (1);
	return (0);
}

t_u_range	wall_range(double wall_height, double vision_height, Uint32 win_h)
{
	t_u_range	wall;

	if (vision_height < wall_height / 2)
		wall.start = 0;
	else
		wall.start = vision_height - wall_height / 2;
	wall.end = vision_height + wall_height / 2;
	wall.end = (wall.end > win_h ? win_h : wall.end);
	return (wall);
}
