/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_mouse_clicks_action.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfatton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/20 05:50:30 by lfatton           #+#    #+#             */
/*   Updated: 2019/04/20 05:50:31 by lfatton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor_mouse_clicks.h"
#include "editor_walls_nodes.h"
#include "in_which_sector.h"
#include "editor_panel_buttons.h"
#include "editor_checks.h"

void	deal_with_clicked_player(t_editor *ed, t_coords *spawn)
{
	ed->selected.p_spawn = spawn;
	ed->dragged.p_spawn = spawn;
}

void	deal_with_clicked_enemy(t_editor *ed, t_enemy *enemy)
{
	ed->selected.enemy = enemy;
	ed->dragged.enemy = enemy;
}

void	deal_with_clicked_pickable(t_editor *ed, t_pickable *pickable)
{
	ed->selected.pickable = pickable;
	ed->dragged.pickable = pickable;
}

void	deal_with_clicked_object(t_editor *ed, t_object *object)
{
	ed->selected.object = object;
	ed->dragged.object = object;
}

void	deal_with_clicked_node(
			t_editor *ed, t_linked_walls *linked, t_coords point)
{
	t_wall_nodes	*list;
	t_linked_walls	*ptr;

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
