#include "editor_walls_nodes.h"
#include "walls.h"
#include "doom.h"

void    move_walls_nodes(t_wall_nodes *nodes, double x, double y)
{
    t_wall_nodes *ptr;

    ptr = nodes;
    while (ptr)
    {
        *ptr->item.x += x / EDITOR_ZOOM;
        *ptr->item.y -= y / EDITOR_ZOOM;
        ptr = ptr->next;
    }
}

void    free_walls_nodes(t_wall_nodes *nodes)
{
    t_wall_nodes *next;

    while (nodes)
    {
        next = nodes->next;
        free(nodes);
        nodes = nodes->next;
    }
}

void    add_wall_node_to_list(t_wall_nodes **list, t_wall *wall, t_coords point)
{
    t_wall_nodes *ptr;
    t_wall_nodes *new;

    if (!(new = (t_wall_nodes *) malloc(sizeof(t_wall_nodes))))
        error_doom("Couldn't malloc wall_nodes");
    new->next = NULL;
    new->item.wall = wall;
    if (fabs(wall->segment.x1 - point.x) < 0.01
    && fabs(wall->segment.y1 - point.y) < 0.01)
    {
        new->item.x = &wall->segment.x1;
        new->item.y = &wall->segment.y1;
    }
    else
    {
        new->item.x = &wall->segment.x2;
        new->item.y = &wall->segment.y2;
    }
    if (!(*list))
    {
        *list = new;
        return;
    }
    ptr = *list;
    while (ptr->next)
        ptr = ptr->next;
    ptr->next = new;
}

void            deal_with_clicked_node(
        t_editor *ed, t_linked_walls *linked, t_coords point)
{
	t_wall_nodes	*list;
    t_linked_walls  *ptr;

    ptr = linked;
    list = NULL;
    add_wall_node_to_list(&list, ptr->wall, point);
	ptr = ptr->next;
	while (ptr->wall)
    {
	    if ((fabs(ptr->wall->segment.x1 - point.x) < 0.001
	    && fabs(ptr->wall->segment.y1 - point.y) < 0.001)
	    || (fabs(ptr->wall->segment.x2 - point.x) < 0.001
	    && fabs(ptr->wall->segment.y2 - point.y) < 0.001))
	        add_wall_node_to_list(&list, ptr->wall, point);
	    ptr = ptr->next;
    }
	ed->selected_nodes = list;
}