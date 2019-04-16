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

void    move_walls_nodes(t_editor *ed, double x, double y)
{
    t_wall_nodes *nodes;

    nodes = ed->dragged.nodes;
    while (nodes)
    {
        *nodes->item.x += x / ed->zoom;
        *nodes->item.y -= y / ed->zoom;
        nodes = nodes->next;
    }
    ed->map_is_updated = t_false;
}

void    move_player_spawn(t_editor *ed, double x, double y)
{
    ed->dragged.p_spawn->x += x / ed->zoom;
    ed->dragged.p_spawn->y -= y / ed->zoom;
    ed->map_is_updated = t_false;
}

void	move_object(t_editor *ed, double x, double y)
{
    ed->dragged.object->x += x / ed->zoom;
    ed->dragged.object->y -= y / ed->zoom;
    ed->map_is_updated = t_false;
}