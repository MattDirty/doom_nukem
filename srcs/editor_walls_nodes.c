#include "editor_walls_nodes.h"
#include "walls.h"
#include "doom.h"

void            deal_with_clicked_nodes(t_wall_nodes *list)
{
    t_wall_nodes *ptr;

    ptr = list;
    while (ptr)
    {
        printf("%p %p\n", ptr->item, list);
        print_segment(&ptr->item->wall->segment, "derp");
        ptr = ptr->next;
    }
}

void    add_wall_node_to_list(t_wall_nodes **list, t_wall *wall, t_coords point)
{
	t_wall_nodes *ptr;

	ptr = *list;
	while (ptr->next)
		ptr = ptr->next;
	if (!(ptr->next = (t_wall_nodes *)malloc(sizeof(t_wall_nodes))))
		error_doom("Couldn't malloc wall_nodes");
	ptr = ptr->next;
	ptr->next = NULL;
	ptr->item = (t_wall_node *)malloc(sizeof(t_wall_node));
	ptr->item->wall = wall;
	if (wall->segment.x1 == point.x && wall->segment.y1 == point.y)
		ptr->item->target_xy = 1;
	else
		ptr->item->target_xy = 2;
}

void            deal_with_clicked_node(t_linked_walls *linked, t_coords point)
{
	t_wall_nodes	*list;
    t_linked_walls  *ptr;

    ptr = linked;
	if (!(list = (t_wall_nodes *)malloc(sizeof(t_wall_nodes))))
		error_doom("Couldn't malloc wall_nodes");
	list->next = NULL;
	list->item = NULL;
    add_wall_node_to_list(&list, ptr->wall, point);
	printf("%p\n", list->item);
	ptr = ptr->next;
	printf("salut\n");
	while (ptr->wall)
    {
	    printf("looping\n");
	    printf("%f, %f, %f, %f\n", ptr->wall->segment.x1, ptr->wall->segment.y1, point.x, point.y);
	    if (ptr->wall->segment.x1 == point.x && ptr->wall->segment.y1 == point.y)
	        add_wall_node_to_list(&list, ptr->wall, point);
	    printf("added wall\n");
	    ptr = ptr->next;
    }
	printf("bye\n");
	deal_with_clicked_nodes(list);
}