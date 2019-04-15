#include "editor_mouse_clicks.h"
#include "editor_walls_nodes.h"

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
	ed->dragged.object = enemy->object;
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