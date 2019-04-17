/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_which_sector.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badhont <badhont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/13 22:56:51 by badhont           #+#    #+#             */
/*   Updated: 2019/04/16 01:45:12 by mtorsell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include "doom.h"
#include "editor.h"

static enum e_bool	line_through_segment_intersects_point(
        t_segment segment,
        double x,
        double y)
{
    double	slope;
    double	ordinate_intercept;
    static const double	epsilon = 0.0001;

    if (segment.x1 == segment.x2)
        return (x == segment.x1);
    slope = (segment.y2 - segment.y1) / (segment.x2 - segment.x1);
    ordinate_intercept = segment.y1 - slope * segment.x1;
    return (fabs(slope * x + ordinate_intercept - y) < epsilon);
}

static enum e_bool	line_through_segment_intersects_a_wall_extremity(
        t_segment segment,
        t_wall *wall)
{
    if (line_through_segment_intersects_point(
                segment,
                wall->segment.x1,
                wall->segment.y1))
        return (e_true);
    if (line_through_segment_intersects_point(
                segment,
                wall->segment.x2,
                wall->segment.y2))
        return (e_true);
    return (e_false);
}

static enum e_bool	line_through_segment_intersects_a_sector_vertex(
        t_segment segment,
        t_sector *sector)
{
    int i;

    i = 0;
    while (i < sector->walls->count)
    {
        if (segments_share_node(&segment, &sector->walls->items[i]->segment))
            return (e_false);
        if (line_through_segment_intersects_a_wall_extremity(
                    segment, sector->walls->items[i]))
            return (e_true);
        i++;
    }
    return (e_false);
}

static void	rotate_segment_around_first_extremity(t_segment *segment, const double angle)
{
    double	cos_angle;
    double	sin_angle;
    double			swap_x;

    cos_angle = cos(angle);
    sin_angle = sin(angle);
    swap_x = segment->x2;
    segment->x2 = cos_angle * (segment->x2 - segment->x1)
        - sin_angle * (segment->y2 - segment->y1) + segment->x1;
    segment->y2 = sin_angle * (swap_x - segment->x1)
        + cos_angle * (segment->y2 - segment->y1) + segment->y1;
}

int     is_in_sector(t_coords pos, t_sector *sector)
{
    t_segment   segment;
    int             i;
    int             intersections_count;
    const double	some_coprime_to_pi_angle = 1.0;

    segment.x1 = pos.x;
    segment.y1 = pos.y;
    segment.x2 = INT_MIN;
    segment.y2 = pos.y;
    while (line_through_segment_intersects_a_sector_vertex(segment, sector))
        rotate_segment_around_first_extremity(
                &segment, some_coprime_to_pi_angle);
    i = 0;
    intersections_count = 0;
    while (i < sector->walls->count)
    {
        if (segments_intersect(
                &segment,
                &sector->walls->items[i]->segment,
                &(t_coords){0, 0}))
            intersections_count++;
        i++;
    }
    return (intersections_count % 2);
}

t_sector	*in_which_sector(t_coords pos, t_sectors *sectors)
{
    int     i;

    i = 0;
    while (i < sectors->count)
    {
        if (is_in_sector(pos, &sectors->items[i]))
            return (&sectors->items[i]);
        i++;
    }
    return (NULL);
}
