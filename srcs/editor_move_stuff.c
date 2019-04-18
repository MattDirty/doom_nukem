#include "utils.h"
#include "editor_walls_nodes.h"
#include "in_which_sector.h"

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

enum e_bool	walls_intersect_on_map(t_linked_walls *linked_walls)
{
	t_linked_walls	*node;
	t_linked_walls	*walls;
	t_coords		inter;

	node = linked_walls;
	while (node->wall)
	{
		walls = node->next;
		while (walls->wall)
		{
			if (segments_intersect(
					&walls->wall->segment, &node->wall->segment, &inter))
			{
				if (!segments_share_node(&walls->wall->segment,
				        &node->wall->segment))
					return (e_true);
			}
			walls = walls->next;
		}
		node = node->next;
	}
	return (e_false);
}

enum e_bool is_object_in_sector(t_sector *sector, t_object *object)
{
    return (is_in_sector((t_coords){object->x, object->y}, sector));
}

enum e_bool are_objects_in_sector_valid(t_sector *sector)
{
    int j;

    j = 0;
    while (j < sector->objects->count)
    {
        if (!is_object_in_sector(sector, &sector->objects->items[j]))
            return (e_false);
        j++;
    }
    return (e_true);
}

enum e_bool are_enemies_in_sector_valid(t_sector *sector)
{
    t_linked_enemies    *e_node;

    e_node = sector->enemies;
    while (e_node)
    {
        if (!is_object_in_sector(sector, e_node->item.object))
            return (e_false);
        e_node = e_node->next;
    }
    return (e_true);
}

enum e_bool is_map_valid(t_linked_walls *walls, t_map *map)
{
    int                 i;
    t_sector            *sector;

    if (walls_intersect_on_map(walls))
        return (e_false);
    if (!in_which_sector(map->spawn, map->sectors))
        return (e_false);
    i = 0;
    while (i < map->sectors->count)
    {
        sector = map->sectors->items[i];
        if (!are_objects_in_sector_valid(sector)
        || !are_enemies_in_sector_valid(sector))
            return (e_false);
        i++;
    }
    return (e_true);
}

void    move_walls_nodes(t_editor *ed, double x, double y)
{
    t_wall_nodes	*nodes;
	double			delta_x;
	double			delta_y;

	nodes = ed->dragged.nodes;
	delta_x = (x - ed->map_offset.x) / ed->zoom - *nodes->item.x;
	delta_y = (ed->map_offset.y - y) / ed->zoom - *nodes->item.y;
    while (nodes)
    {
        *nodes->item.x += delta_x;
        *nodes->item.y += delta_y;
        nodes = nodes->next;
    }
    nodes = ed->dragged.nodes;
    if (!is_map_valid(ed->linked_walls, ed->map))
	{
    	while (nodes)
		{
    		*nodes->item.x -= delta_x;
    		*nodes->item.y -= delta_y;
    		nodes = nodes->next;
		}
        Mix_PlayChannel(-1, ed->sounds->meeeh, 0);
    	return;
	}
    ed->map_is_updated = e_false;
}

void    move_player_spawn(t_editor *ed, double x, double y)
{
    t_sector *sector;
    double   new_x;
    double   new_y;

    new_x = (x - ed->map_offset.x) / ed->zoom;
    new_y = (ed->map_offset.y - y) / ed->zoom;
    if (!(sector = in_which_sector((t_coords){new_x, new_y},ed->map->sectors)))
    {
        Mix_PlayChannel(-1, ed->sounds->meeeh, 0);
        return;
    }
    ed->map->spawn.x = new_x;
    ed->map->spawn.y = new_y;
    ed->map_is_updated = e_false;
}

void	move_enemy(t_editor *ed, double x, double y)
{
	t_sector	*sector;
	double		new_x;
	double		new_y;

	sector = find_enemy_sector(ed->map->sectors, ed->dragged.enemy);
	new_x = (x - ed->map_offset.x) / ed->zoom;
	new_y = (ed->map_offset.y - y) / ed->zoom;
	if (!is_in_sector((t_coords){new_x, new_y}, sector))
    {
        Mix_PlayChannel(-1, ed->sounds->meeeh, 0);
	    return ;
    }
	ed->dragged.enemy->object->x = new_x;
	ed->dragged.enemy->object->y = new_y;
	ed->map_is_updated = e_false;
}

void	move_pickable(t_editor *ed, double x, double y)
{
    t_sector	*sector;
    double		new_x;
    double		new_y;

    sector = find_pickable_sector(ed->map->sectors, ed->dragged.pickable);
    new_x = (x - ed->map_offset.x) / ed->zoom;
    new_y = (ed->map_offset.y - y) / ed->zoom;
    if (!is_in_sector((t_coords){new_x, new_y}, sector))
    {
        Mix_PlayChannel(-1, ed->sounds->meeeh, 0);
        return ;
    }
    ed->dragged.pickable->object->x = new_x;
    ed->dragged.pickable->object->y = new_y;
    ed->map_is_updated = e_false;
}

void	move_object(t_editor *ed, double x, double y)
{
	t_sector	*sector;
	double	new_x;
	double	new_y;

	sector = find_object_sector(ed->map->sectors, ed->dragged.object);
	new_x = (x - ed->map_offset.x) / ed->zoom;
	new_y = (ed->map_offset.y - y) / ed->zoom;
	if (!is_in_sector((t_coords){new_x, new_y}, sector))
    {
        Mix_PlayChannel(-1, ed->sounds->meeeh, 0);
	    return ;
    }
    ed->dragged.object->x = new_x;
    ed->dragged.object->y = new_y;
    ed->map_is_updated = e_false;
}
