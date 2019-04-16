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

int     is_in_sector(t_coords pos, t_sector *sector)
{
    t_segment   segment;
    int         i;
    int         intersections_count;

    segment.x1 = INT_MIN;
    segment.y1 = pos.y;
    segment.x2 = pos.x;
    segment.y2 = pos.y;
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
