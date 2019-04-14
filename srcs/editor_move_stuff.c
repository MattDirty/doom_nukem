#include "utils.h"
#include "editor_walls_nodes.h"

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

void    move_player_spawn(t_coords *spawn, double x, double y)
{
    spawn->x += x / EDITOR_ZOOM;
    spawn->y -= y / EDITOR_ZOOM;
}

void	move_object(t_object *object, double x, double y)
{
	object->x += x / EDITOR_ZOOM;
	object->y -= y / EDITOR_ZOOM;
}