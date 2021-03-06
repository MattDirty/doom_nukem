#include "editor_mouse_clicks.h"
#include "editor_panel_buttons.h"
#include "in_which_sector.h"

enum e_bool		click_on_sector(t_editor *ed, t_map *map, int mouse_x, int mouse_y)
{
	ed->selected.sector = in_which_sector(
            (t_coords){
                    ((double)mouse_x - ed->map_offset.x) / ed->zoom,
                    ((double)-mouse_y + ed->map_offset.y) / ed->zoom},
            map->sectors);
	if (!ed->selected.sector)
		return (e_false);
	deal_with_clicked_sector(ed);
	return (e_true);
}

enum e_bool     click_on_player(t_editor *ed, t_map *map, int x, int y)
{
	t_rect  rect;

	rect = create_rect(ed->map_offset.x + map->spawn.x * ed->zoom - 10,
					   ed->map_offset.y - map->spawn.y * ed->zoom - 10,
					   20, 20);
	if (is_in_rect(&rect, x, y))
	{
		deal_with_clicked_player(ed, &map->spawn);
		return (e_true);
	}
	return (e_false);
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
		sector = map->sectors->items[i];
		j = 0;
		while (j < sector->objects->count)
		{
			rect = create_rect(ed->map_offset.x + sector->objects->items[j].x * ed->zoom - 6,
							   ed->map_offset.y - sector->objects->items[j].y * ed->zoom - 6,
							   12, 12);
			if (is_in_rect(&rect, mouse_x, mouse_y))
			{
				deal_with_clicked_object(ed, &sector->objects->items[j]);
				return (e_true);
			}
			j++;
		}
		i++;
	}
	return (e_false);
}

enum e_bool		click_on_enemy(t_editor *ed, t_map *map, int mouse_x, int mouse_y)
{
	int			i;
    t_linked_enemies	*enemies;
	t_sector	*sector;
	t_rect		rect;

	i = 0;
	while (i < map->sectors->count)
	{
		sector = map->sectors->items[i];
        enemies = sector->enemies;
		while (enemies)
		{
			rect = create_rect(
                    ed->map_offset.x + enemies->item.object->x
                            * ed->zoom - 6,
                    ed->map_offset.y - enemies->item.object->y
                            * ed->zoom - 6,
                    12, 12);
			if (is_in_rect(&rect, mouse_x, mouse_y))
			{
				deal_with_clicked_enemy(ed, &enemies->item);
				return (e_true);
			}
            enemies = enemies->next;
		}
		i++;
	}
	return (e_false);
}

enum e_bool		click_on_pickable(t_editor *ed, t_map *map, int mouse_x, int mouse_y)
{
    int			i;
    t_pickables	*pickables;
    t_sector	*sector;
    t_rect		rect;

    i = 0;
    while (i < map->sectors->count)
    {
        sector = map->sectors->items[i];
        pickables = sector->pickables;
        while (pickables)
        {
            rect = create_rect(
                    ed->map_offset.x + pickables->item.object->x
                                       * ed->zoom - 6,
                    ed->map_offset.y - pickables->item.object->y
                                       * ed->zoom - 6,
                    12, 12);
            if (is_in_rect(&rect, mouse_x, mouse_y))
            {
                deal_with_clicked_pickable(ed, &pickables->item);
                return (e_true);
            }
            pickables = pickables->next;
        }
        i++;
    }
    return (e_false);
}

enum e_bool     click_on_walls(t_editor *ed, t_linked_walls *linked_walls, int mouse_x, int mouse_y)
{
	t_linked_walls *ptr;

	ptr = linked_walls;
	while (ptr->wall)
	{
		if (is_on_seg(ptr->wall->segment, (t_i_coords){mouse_x, mouse_y}, ed->map_offset, ed->zoom))
		{
			ed->selected.wall = ptr->wall;
			return (e_true);
		}
		ptr = ptr->next;
	}
	return (e_false);
}

enum e_bool     click_on_panel(t_editor *ed, int mouse_x, int mouse_y)
{
    t_buttons    *buttons;

    if (mouse_x < PANEL_X)
        return (e_false);
    buttons = ed->panel.buttons;
    while (buttons)
    {
        if (is_in_rect(&buttons->item.rect, mouse_x, mouse_y))
        {
            buttons->item.f((t_params)buttons->item.params);
            return (e_true);
        }
        buttons = buttons->next;
    }
    clear_selection(&ed->dragged);
    ed->state = e_null;
    return (e_true);
}

enum e_bool     click_on_nodes(t_editor *ed, t_linked_walls *linked_walls, int x, int y)
{
	t_linked_walls *ptr;
	t_rect rect;

	ptr = linked_walls;
	while (ptr->wall)
	{
		rect = create_rect(
				ed->map_offset.x + ptr->wall->segment.x1 * ed->zoom - CORNER_SIZE / 2,
				ed->map_offset.y - ptr->wall->segment.y1 * ed->zoom - CORNER_SIZE / 2,
				CORNER_SIZE, CORNER_SIZE);
		if (is_in_rect(&rect, x, y))
		{
			deal_with_clicked_node(ed, ptr, (t_coords){ptr->wall->segment.x1, ptr->wall->segment.y1});
			return (e_true);
		}
		rect = create_rect(ed->map_offset.x + ptr->wall->segment.x2 * ed->zoom - CORNER_SIZE / 2,
				ed->map_offset.y - ptr->wall->segment.y2 * ed->zoom
				- CORNER_SIZE / 2, CORNER_SIZE, CORNER_SIZE);
		if (is_in_rect(&rect, x, y))
		{
			deal_with_clicked_node(ed, ptr, (t_coords){ptr->wall->segment.x2, ptr->wall->segment.y2});
			return (e_true);
		}
		ptr = ptr->next;
	}
	return (e_false);
}
