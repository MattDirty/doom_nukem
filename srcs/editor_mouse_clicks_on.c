#include "editor_mouse_clicks.h"

enum e_bool     click_on_player(t_editor *ed, t_map *map, int x, int y)
{
	t_rect  rect;

	rect = create_rect(DRAW_MAP_X + map->spawn.x * EDITOR_ZOOM - 10,
					   DRAW_MAP_Y - map->spawn.y * EDITOR_ZOOM - 10,
					   20, 20);
	if (is_in_rect(&rect, x, y))
	{
		deal_with_clicked_player(ed, &map->spawn);
		return (t_true);
	}
	return (t_false);
}

enum e_bool		click_on_object(t_editor *ed, t_map *map, int mouse_x, int mouse_y)
{
	int			i;
	int			j;
	t_sector	*sector;
	t_rect		rect;

	i = 0;
	while (i < map->sectors->count)
	{
		sector = &map->sectors->items[i];
		j = 0;
		while (j < sector->objects->count)
		{
			rect = create_rect(DRAW_MAP_X + sector->objects->items[j].x * EDITOR_ZOOM - 6,
							   DRAW_MAP_Y - sector->objects->items[j].y * EDITOR_ZOOM - 6,
							   12, 12);
			if (is_in_rect(&rect, mouse_x, mouse_y))
			{
				deal_with_clicked_object(ed, &sector->objects->items[j]);
				return (t_true);
			}
			j++;
		}
		i++;
	}
	return (t_false);
}

enum e_bool		click_on_enemy(t_editor *ed, t_map *map, int mouse_x, int mouse_y)
{
	int			i;
	int			j;
	t_sector	*sector;
	t_rect		rect;

	i = 0;
	while (i < map->sectors->count)
	{
		sector = &map->sectors->items[i];
		j = 0;
		while (j < sector->enemies->count)
		{
			rect = create_rect(DRAW_MAP_X + sector->enemies->items[j].object->x * EDITOR_ZOOM - 6,
								DRAW_MAP_Y - sector->enemies->items[j].object->y * EDITOR_ZOOM - 6,
								12, 12);
			if (is_in_rect(&rect, mouse_x, mouse_y))
			{
				deal_with_clicked_enemy(ed, &sector->enemies->items[j]);
				return (t_true);
			}
			j++;
		}
		i++;
	}
	return (t_false);
}

enum e_bool     click_on_walls(t_editor *ed, t_linked_walls *linked_walls, int mouse_x, int mouse_y)
{
	t_linked_walls *ptr;

	ptr = linked_walls;
	(void)ed;
	while (ptr->wall)
	{
		if (is_on_seg(ptr->wall->segment, mouse_x, mouse_y))
		{
			printf("blop\n");
			return (t_true);
		}
		ptr = ptr->next;
	}
	return (t_false);
}

enum e_bool     click_on_panel(t_editor *ed, t_buttons *buttons, int mouse_x, int mouse_y)
{
	int i;

	if (mouse_x < PANEL_X)
		return (t_false);
	i = 0;
	while (i < buttons->count)
	{
		if (is_in_rect(&buttons->items[i].rect, mouse_x, mouse_y))
		{
			buttons->items[i].f(ed, &buttons->items[i].rect);
			return (t_true);
		}
		i++;
	}
	return (t_false);
}

enum e_bool     click_on_nodes(t_editor *ed, t_linked_walls *linked_walls, int x, int y)
{
	t_linked_walls *ptr;
	t_rect rect;

	ptr = linked_walls;
	while (ptr->wall)
	{
		rect = create_rect(
				DRAW_MAP_X + ptr->wall->segment.x1 * EDITOR_ZOOM - CORNER_SIZE / 2,
				DRAW_MAP_Y - ptr->wall->segment.y1 * EDITOR_ZOOM - CORNER_SIZE / 2,
				CORNER_SIZE, CORNER_SIZE);
		if (is_in_rect(&rect, x, y))
		{
			deal_with_clicked_node(ed, ptr, (t_coords){ptr->wall->segment.x1, ptr->wall->segment.y1});
			free_linked_walls_nodes(linked_walls);
			return (t_true);
		}
		rect = create_rect(DRAW_MAP_X + ptr->wall->segment.x2 * EDITOR_ZOOM - CORNER_SIZE / 2, DRAW_MAP_Y
																							   - ptr->wall->segment.y2 * EDITOR_ZOOM - CORNER_SIZE / 2, CORNER_SIZE, CORNER_SIZE);
		if (is_in_rect(&rect, x, y))
		{
			deal_with_clicked_node(ed, ptr, (t_coords){ptr->wall->segment.x2, ptr->wall->segment.y2});
			free_linked_walls_nodes(linked_walls);
			return (t_true);
		}
		ptr = ptr->next;
	}
	return (t_false);
}