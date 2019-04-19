#include "walls.h"
#include "editor.h"
#include "in_which_sector.h"

enum e_bool segment_intersect_with_map(t_linked_walls *walls, t_segment seg)
{
	t_linked_walls	*n;
	t_coords		inter;

	n = walls;
	while (n->wall)
	{
		if (segments_intersect(&seg, &n->wall->segment, &inter))
		{
			if (!segments_share_node(&seg, &n->wall->segment))
				return (e_true);
		}
		n = n->next;
	}
	return (e_false);
}

enum e_bool	new_node_pos_valid(t_editor *ed, t_coords pos)
{
	return (in_which_sector(pos, ed->map->sectors)
			|| segment_intersect_with_map(
			ed->linked_walls,
			(t_segment){
					pos.x,
					pos.y,
					ed->selected.wall->segment.x1,
					ed->selected.wall->segment.y1})
			|| segment_intersect_with_map(
			ed->linked_walls,
			(t_segment){
					pos.x,
					pos.y,
					ed->selected.wall->segment.x2,
					ed->selected.wall->segment.y2})
	);
}