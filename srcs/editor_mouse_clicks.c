#include "e_bool.h"
#include "editor.h"
#include "editor_draw.h"
#include "editor_walls_nodes.h"
#include "map.h"

enum e_bool     click_on_nodes(t_editor *ed, t_map *map, int x, int y)
{
    t_linked_walls *linked_walls;
    t_linked_walls *ptr;
    int count;
    t_rect rect;

    create_linked_walls_from_sectors(map->sectors, &linked_walls, &count);
    ptr = linked_walls;
    while (ptr->wall)
    {
        rect = create_rect(DRAW_MAP_X + ptr->wall->segment.x1 * EDITOR_ZOOM - CORNER_SIZE / 2, DRAW_MAP_Y
        - ptr->wall->segment.y1 * EDITOR_ZOOM - CORNER_SIZE / 2, CORNER_SIZE, CORNER_SIZE);
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
    free_linked_walls_nodes(linked_walls);
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

void    mouseup_action(t_editor *ed, int mouse_x, int mouse_y)
{
    (void)mouse_x; (void)mouse_y;
    if (ed->selected_nodes)
    {
        free_walls_nodes(ed->selected_nodes);
    }
    ed->selected_nodes = NULL;
}

void    mousedown_action(t_editor *ed, int mouse_x, int mouse_y)
{
    if (click_on_panel(ed, &ed->buttons, mouse_x, mouse_y))
        return ;
    if (click_on_nodes(ed, ed->map, mouse_x, mouse_y))
        return ;
}