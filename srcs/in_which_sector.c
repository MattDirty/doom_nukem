/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_which_sector.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badhont <badhont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/13 22:56:51 by badhont           #+#    #+#             */
/*   Updated: 2019/04/14 06:32:37 by badhont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "editor.h"

static int	max(int a, int b)
{
	return (a > b ? a : b);
}

static int	min(int a, int b)
{
	return (a < b ? a : b);
}

int			onSegment(t_i_coords p, t_i_coords q, t_i_coords r)
{
	if (q.x <= max(p.x, r.x) && q.x >= min(p.x, r.x)
	&& q.y <= max(p.y, r.y) && q.y >= min(p.y, r.y))
		return (1);
	return (0);
}

static int	orientation(t_i_coords p, t_i_coords q, t_i_coords r)
{
	float val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);

	if (val == 0)
		return (0);
	return (val > 0) ? 1 : 2;
}

int		intersect_segment(t_i_coords p1, t_i_coords q1, t_i_coords p2, t_i_coords q2)
{
	//Find the four orientations needed for general and
	// special cases
	float o1 = orientation(p1, q1, p2);
	float o2 = orientation(p1, q1, q2);
	float o3 = orientation(p2, q2, p1);
	float o4 = orientation(p2, q2, q1);

	// General case
	if (o1 != o2 && o3 != o4)
		return (1);

	// Special Cases
	// p1, q1 and p2 are colinear and p2 lies on segment p1q1
	if (o1 == 0 && onSegment(p1, p2, q1))
		return (1);

	// p1, q1 and q2 are colinear and q2 lies on segment p1q1
	if (o2 == 0 && onSegment(p1, q2, q1))
		return (1);

	// p2, q2 and p1 are colinear and p1 lies on segment p2q2
	if (o3 == 0 && onSegment(p2, p1, q2))
		return (1);

	// p2, q2 and q1 are colinear and q1 lies on segment p2q2
	if (o4 == 0 && onSegment(p2, q1, q2))
		return (1);

	return (0); // Doesn't fall in any of the above cases
}

int     is_in_sector(t_i_coords pos, t_sector sector, t_editor *ed)
{	
    t_segment   segment;
    t_segment   edge;
	t_segment   edge2;
    int         i;
    int         value;

    /*s = sectors.walls->items[i]->segment;
    edge2.x1 = DRAW_MAP_X + edge.x1 * EDITOR_ZOOM;
    edge2.y1 = DRAW_MAP_Y - edge.y1 * EDITOR_ZOOM;
    edge2.x2 = DRAW_MAP_X + edge.x2 * EDITOR_ZOOM;
	edge2.y2 = DRAW_MAP_Y - edge.y2 * EDITOR_ZOOM;*/

	(void)ed;
    segment.x1 = 0;
    segment.y1 = pos.y;
    segment.x2 = pos.x;
    segment.y2 = pos.y;
    i = 0;
    value = 0;
    while (i < sector.walls->count)
    {
        edge = sector.walls->items[i]->segment;
		edge2.x1 = DRAW_MAP_X + edge.x1 * EDITOR_ZOOM;
    	edge2.y1 = DRAW_MAP_Y - edge.y1 * EDITOR_ZOOM;
	    edge2.x2 = DRAW_MAP_X + edge.x2 * EDITOR_ZOOM;
		edge2.y2 = DRAW_MAP_Y - edge.y2 * EDITOR_ZOOM;
        if (intersect_segment(
        (t_i_coords){segment.x1, segment.y1},
        (t_i_coords){segment.x2, segment.y2},
        (t_i_coords){edge.x1, edge.y1},
        (t_i_coords){edge.x2, edge.y2}))
            value++;
        i++;
    }
	printf("mouse x : %f\n", segment.x2);
	printf("mouse y : %f\n", segment.y2);
	printf("edge x1: %f\n", edge.x1);
	printf("edge y1: %f\n", edge.y1);
	printf("edge x2: %f\n", edge.x2);
	printf("edge y2: %f\n", edge.y2);
	
	printf("nb de murs traversés : %d\n", value);
    //draw_segment(ed->sdl.surface, segment, 0xFFFFFFFF); // todel
    return (value % 2);
}


int     in_which_sector(t_i_coords pos, t_sectors sectors, t_editor *ed)
{
    int     i;

    i = 0;
    while (i < sectors.count)
    {
		printf("i (sectors) : %d\n", i);
        if (is_in_sector(pos, sectors.items[i], ed))
            return (i);
        i++;
    }
    return (-1);
}