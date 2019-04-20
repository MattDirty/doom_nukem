/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_checks.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfatton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/20 04:17:44 by lfatton           #+#    #+#             */
/*   Updated: 2019/04/20 04:17:50 by lfatton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "walls.h"
#include "editor.h"
#include "in_which_sector.h"
#include "utils.h"

enum e_bool	segment_intersect_with_map(t_linked_walls *walls, t_segment seg)
{
	t_linked_walls	*node;
	t_coords		inter;

	node = walls;
	while (node->wall)
	{
		if (segments_intersect(&seg, &node->wall->segment, &inter))
		{
			if (!segments_share_node(&seg, &node->wall->segment))
				return (e_true);
		}
		node = node->next;
	}
	return (e_false);
}

enum e_bool	new_node_pos_valid(t_editor *ed, t_coords pos)
{
	t_segment	seg1;
	t_segment	seg2;

	seg1 = create_segment(pos.x, pos.y, ed->selected.wall->segment.x1,
			ed->selected.wall->segment.y1);
	seg2 = create_segment(pos.x, pos.y, ed->selected.wall->segment.x1,
			ed->selected.wall->segment.y2);
	return (in_which_sector(pos, ed->map->sectors)
		|| segment_intersect_with_map(ed->linked_walls, seg1)
		|| segment_intersect_with_map(ed->linked_walls, seg2));
}
