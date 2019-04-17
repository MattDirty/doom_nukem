#include "editor_mouse_clicks.h"
#include "editor_walls_nodes.h"
#include "in_which_sector.h"
#include "editor_panel_buttons.h"

void        create_object_in_sector(t_editor *ed, int mouse_x, int mouse_y)
{
    t_coords    pos;
    t_sector    *sector;

    pos.x = (mouse_x - ed->map_offset.x) / ed->zoom;
    pos.y = (ed->map_offset.y - mouse_y) / ed->zoom;
    sector = in_which_sector(pos, ed->map->sectors);
    if (!sector)
        printf("oups\n");
    else
        printf("yup\n");
    ed->state = e_null;
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