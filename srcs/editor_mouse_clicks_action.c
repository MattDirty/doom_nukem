#include "editor_mouse_clicks.h"
#include "editor_walls_nodes.h"
#include "in_which_sector.h"
#include "editor_panel_buttons.h"
#include "editor_checks.h"

void		copy_sector_floor_ceil(t_sector *target, t_sector *source)
{
	target->ceil = source->ceil;
	target->floor = source->floor;
	target->open_sky = source->open_sky;
}

void		try_sector_creation(t_editor *ed, int mouse_x, int mouse_y)
{
	t_coords	pos;
	t_wall		*wall;
	t_sector	*new_sector;
	t_sector	*linked_sector;

	ed->state = e_null;
	pos.x = (double)(mouse_x - ed->map_offset.x) / ed->zoom;
	pos.y = (double)(ed->map_offset.y - mouse_y) / ed->zoom;
	if (new_node_pos_valid(ed, pos))
		return ;
	new_sector = create_new_sector(ed->map->sectors);
	linked_sector = find_wall_sector(ed->map->sectors, ed->selected.wall);
	copy_sector_floor_ceil(new_sector, linked_sector);
	wall = create_wall_copy(ed->selected.wall);
	wall->segment.x1 = pos.x;
	wall->segment.y1 = pos.y;
	add_wall_to_sector(new_sector, wall);
	wall = create_wall_copy(ed->selected.wall);
	wall->segment.x2 = pos.x;
	wall->segment.y2 = pos.y;
	add_wall_to_sector(new_sector, wall);
	transform_wall_to_portal(ed->selected.wall, linked_sector, new_sector);
	add_wall_to_sector(new_sector, ed->selected.wall);
	free_linked_walls_nodes(ed->linked_walls);
	create_linked_walls_from_sectors(
			ed->map->sectors, &ed->linked_walls, &ed->linked_walls_count);
}

void        create_object_in_sector(t_editor *ed, int mouse_x, int mouse_y)
{
    t_coords    pos;
    t_sector    *sector;

    pos.x = (double)(mouse_x - ed->map_offset.x) / ed->zoom;
    pos.y = (double)(ed->map_offset.y - mouse_y) / ed->zoom;
    sector = in_which_sector(pos, ed->map->sectors);
    if (sector)
        ed->selected.object = add_new_object_to_sector_at_pos(
                sector, pos, ed->textures);
    if (!ed->selected.object)
        Mix_PlayChannel(-1, ed->sounds->meeeh, 0);
    ed->state = e_null;
    ed->map_is_updated = e_false;
}

void        create_enemy_in_sector(t_editor *ed, int mouse_x, int mouse_y)
{
    t_coords    pos;
    t_sector    *sector;
    t_linked_enemies    *enemy;

    pos.x = (double)(mouse_x - ed->map_offset.x) / ed->zoom;
    pos.y = (double)(ed->map_offset.y - mouse_y) / ed->zoom;
    sector = in_which_sector(pos, ed->map->sectors);
    if (sector)
    {
        enemy = add_new_enemy_to_sector_at_pos(sector, pos, ed->textures);
        if (!enemy)
            ed->selected.enemy = NULL;
        else
            ed->selected.enemy = &enemy->item;
    }
    if (!ed->selected.enemy)
        Mix_PlayChannel(-1, ed->sounds->meeeh, 0);
    ed->state = e_null;
	ed->map_is_updated = e_false;
}

void        create_pickable_in_sector(t_editor *ed, int mouse_x, int mouse_y)
{
	t_coords    pos;
	t_sector    *sector;
	t_pickables	*pickables;

	pos.x = (double)(mouse_x - ed->map_offset.x) / ed->zoom;
	pos.y = (double)(ed->map_offset.y - mouse_y) / ed->zoom;
	sector = in_which_sector(pos, ed->map->sectors);
	if (sector)
	{
		pickables = add_new_pickable_to_sector_at_pos(sector, pos, ed->textures);
		if (!pickables)
			ed->selected.pickable = NULL;
		else
			ed->selected.pickable = &pickables->item;
	}
	if (!ed->selected.pickable)
		Mix_PlayChannel(-1, ed->sounds->meeeh, 0);
	ed->state = e_null;
	ed->map_is_updated = e_false;
}

void			deal_with_clicked_sector(t_editor *ed)
{
	(void)ed;
}

void            deal_with_clicked_player(t_editor *ed, t_coords *spawn)
{
	ed->selected.p_spawn = spawn;
	ed->dragged.p_spawn = spawn;
}

void			deal_with_clicked_enemy(t_editor *ed, t_enemy *enemy)
{
	ed->selected.enemy = enemy;
	ed->dragged.enemy = enemy;
}

void			deal_with_clicked_pickable(t_editor *ed, t_pickable *pickable)
{
    ed->selected.pickable = pickable;
    ed->dragged.pickable = pickable;
}

void			deal_with_clicked_object(t_editor *ed, t_object *object)
{
	ed->selected.object = object;
	ed->dragged.object = object;
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
	ed->dragged.nodes = list;
}
