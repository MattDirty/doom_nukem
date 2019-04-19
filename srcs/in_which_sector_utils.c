/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_which_sector_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfatton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/20 01:32:15 by lfatton           #+#    #+#             */
/*   Updated: 2019/04/20 01:32:17 by lfatton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "utils.h"
#include "default.h"
#include "sectors.h"

static enum e_bool	line_through_segment_intersects_point(
						t_segment segment, double x, double y)
{
	double				slope;
	double				ordinate_intercept;

	if (segment.x1 == segment.x2)
		return (x == segment.x1);
	slope = (segment.y2 - segment.y1) / (segment.x2 - segment.x1);
	ordinate_intercept = segment.y1 - slope * segment.x1;
	return (fabs(slope * x + ordinate_intercept - y) < EPSILON);
}

static enum e_bool	line_through_segment_intersects_a_wall_extremity(
		t_segment segment, t_wall *wall)
{
	if (line_through_segment_intersects_point(segment, wall->segment.x1,
			wall->segment.y1))
		return (e_true);
	if (line_through_segment_intersects_point(segment, wall->segment.x2,
			wall->segment.y2))
		return (e_true);
	return (e_false);
}

enum e_bool			line_through_segment_intersects_a_sector_vertex(
						t_segment segment, t_sector *sector)
{
	int	i;

	i = 0;
	while (i < sector->walls->count)
	{
		if (segments_share_node(&segment, &sector->walls->items[i]->segment))
			return (e_false);
		if (line_through_segment_intersects_a_wall_extremity(segment,
				sector->walls->items[i]))
			return (e_true);
		i++;
	}
	return (e_false);
}

void				rotate_segment_around_first_extremity(
						t_segment *segment, const double angle)
{
	double cos_angle;
	double sin_angle;
	double swap_x;

	cos_angle = cos(angle);
	sin_angle = sin(angle);
	swap_x = segment->x2;
	segment->x2 = cos_angle * (segment->x2 - segment->x1) - sin_angle * (
			segment->y2 - segment->y1) + segment->x1;
	segment->y2 = sin_angle * (swap_x - segment->x1) + cos_angle * (segment->y2
			- segment->y1) + segment->y1;
}
