/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_which_sector.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badhont <badhont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/13 22:56:51 by badhont           #+#    #+#             */
/*   Updated: 2019/04/14 20:20:40 by badhont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "editor.h"

int     is_in_sector(t_i_coords pos, t_sector sector)
{
    t_segment   segment;
    t_segment   edge;
    int         i;
    int         value;

    segment.x1 = 0;
    segment.y1 = pos.y;
    segment.x2 = pos.x;
    segment.y2 = pos.y;
    i = 0;
    value = 0;
    while (i < sector.walls->count)
    {
        edge = sector.walls->items[i]->segment;
		edge.x1 = DRAW_MAP_X + edge.x1 * EDITOR_ZOOM;
    	edge.y1 = DRAW_MAP_Y - edge.y1 * EDITOR_ZOOM;
	    edge.x2 = DRAW_MAP_X + edge.x2 * EDITOR_ZOOM;
		edge.y2 = DRAW_MAP_Y - edge.y2 * EDITOR_ZOOM;
        if (segments_intersect(&segment, &edge, &(t_coords){0, 0}))
            value++;
        i++;
    }
    return (value % 2);
}


t_sector	*in_which_sector(t_i_coords pos, t_sectors *sectors)
{
    int     i;

    i = 0;
    while (i < sectors->count)
    {
        if (is_in_sector(pos, sectors->items[i]))
            return (&(sectors->items[i]));
        i++;
    }
    return (NULL);
}