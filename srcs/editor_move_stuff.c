#include "utils.h"
#include "editor_walls_nodes.h"

void	move_map(t_editor *ed, SDL_Scancode key)
{
    if (key == SDL_SCANCODE_UP)
        ed->map_offset.y += 0.5 * ed->zoom;
    if (key == SDL_SCANCODE_DOWN)
        ed->map_offset.y -= 0.5 * ed->zoom;;
    if (key == SDL_SCANCODE_LEFT)
        ed->map_offset.x += 0.5 * ed->zoom;;
    if (key == SDL_SCANCODE_RIGHT)
        ed->map_offset.x -= 0.5 * ed->zoom;;
}

void    move_walls_nodes(t_wall_nodes *nodes, double x, double y, int zoom)
{
    t_wall_nodes *ptr;

    ptr = nodes;
    while (ptr)
    {
        *ptr->item.x += x / zoom;
        *ptr->item.y -= y / zoom;
        ptr = ptr->next;
    }
}

void    move_player_spawn(t_coords *spawn, double x, double y, int zoom)
{
    spawn->x += x / zoom;
    spawn->y -= y / zoom;
}

void	move_object(t_object *object, double x, double y, int zoom)
{
	object->x += x / zoom;
	object->y -= y / zoom;
}