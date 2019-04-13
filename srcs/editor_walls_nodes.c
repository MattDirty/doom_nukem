#include "editor_walls_nodes.h"

void			add_wall_node_to_list(t_wall_nodes *list, t_wall *wall, t_coords point)
{
	t_wall_nodes *ptr;

	ptr = list;
	while (ptr->next)
		ptr = ptr->next;
	if (!(ptr->next = (t_wall_nodes *)malloc(sizeof(t_wall_nodes))))
		error_doom("Couldn't malloc wall_nodes");
	ptr = ptr->next;
	ptr->next = NULL;
	ptr->item->wall = wall;
	if (wall->segment.x1 == point.x && wall->segment.y1 == point.y)
		ptr->item->target_xy = 1;
	else
		ptr->item->target_xy = 2;
}

void            deal_with_clicked_node(t_linked_walls *ptr, t_coords point)
{
	t_wall_nodes	*list;

	if (!(list = (t_wall_nodes *)malloc(sizeof(t_wall_nodes))))
		error_doom("Couldn't malloc wall_nodes");
	list->next = NULL;
	list->item = NULL;
	add_wall_node_to_list(list, ptr->item, point);
}