#include "editor_mouse_clicks.h"
#include "editor_walls_nodes.h"
#include "in_which_sector.h"
#include "editor_panel_buttons.h"

void		try_sector_creation(t_editor *ed, int mouse_x, int mouse_y)
{
	t_coords	pos;
	t_wall		*wall;
	t_sector	*new_sector;

	pos.x = (double)(mouse_x - ed->map_offset.x) / ed->zoom;
	pos.y = (double)(ed->map_offset.y - mouse_y) / ed->zoom;
	if (in_which_sector(pos, ed->map->sectors))
		return ;
	printf("salut\n");
	new_sector = create_new_sector(ed->map->sectors);
	add_wall_to_sector(new_sector, ed->selected.wall);
	wall = create_wall_copy(ed->selected.wall);
	wall->segment.x1 = pos.x;
	wall->segment.y1 = pos.y;
	add_wall_to_sector(new_sector, wall);
	wall = create_wall_copy(ed->selected.wall);
	wall->segment.x2 = pos.x;
	wall->segment.y2 = pos.y;
	add_wall_to_sector(new_sector, wall);
	ed->selected.wall->type = e_portal;
	ed->selected.wall->texture = NULL;

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
}

void        create_enemy_in_map(t_params params)
{
    ((t_btn_params *)params)->ed->state = e_add_enemy;
}

void        create_object_in_map(t_params params)
{
    ((t_btn_params *)params)->ed->state = e_add_object;
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