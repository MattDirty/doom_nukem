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

enum e_bool	move_created_intersections(t_editor *ed)
{
	t_linked_walls	*node;
	t_linked_walls	*walls;
	t_coords		inter;

	node = ed->linked_walls;
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
					return (t_true);
			}
			walls = walls->next;
		}
		node = node->next;
	}
	return (t_false);
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
    if (move_created_intersections(ed))
	{
    	while (nodes)
		{
    		*nodes->item.x -= delta_x;
    		*nodes->item.y -= delta_y;
    		nodes = nodes->next;
		}
    	return;
	}
    ed->map_is_updated = t_false;
}

void    move_player_spawn(t_editor *ed, double x, double y)
{
    t_sector *sector;
    double   new_x;
    double   new_y;

    new_x = (x - ed->map_offset.x) / ed->zoom;
    new_y = (ed->map_offset.y - y) / ed->zoom;
    if (!(sector = in_which_sector((t_coords){new_x, new_y},ed->map->sectors)))
        return;
    ed->map->spawn.x = new_x;
    ed->map->spawn.y = new_y;
    ed->map->player_spawn_index = sector_index(ed->map->sectors, sector);
    ed->map_is_updated = t_false;
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
		return ;
	ed->dragged.enemy->object->x = new_x;
	ed->dragged.enemy->object->y = new_y;
	ed->map_is_updated = t_false;
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
		return ;
    ed->dragged.object->x = new_x;
    ed->dragged.object->y = new_y;
    ed->map_is_updated = t_false;
}