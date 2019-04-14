#include "e_bool.h"
#include "editor.h"
#include "editor_draw.h"
#include "editor_walls_nodes.h"
#include "editor_mouse_clicks.h"
#include "map.h"

t_segment       transform_seg_in_ed_coords(t_segment seg)
{
    seg.x1 = DRAW_MAP_X + seg.x1 * EDITOR_ZOOM;
    seg.x2 = DRAW_MAP_X + seg.x2 * EDITOR_ZOOM;
    seg.y1 = DRAW_MAP_Y - seg.y1 * EDITOR_ZOOM;
    seg.y2 = DRAW_MAP_Y - seg.y2 * EDITOR_ZOOM;
    return(seg);
}

enum e_bool     check_delta(double delta_x, double delta_y, t_segment seg, t_i_coords mouse)
{
    if (!delta_x)
    {
        if ((fabs(seg.x1 - mouse.x) <= 5) && ((mouse.y <= seg.y1
            && mouse.y >= seg.y2) || (mouse.y <= seg.y2 && mouse.y >= seg.y1)))
            return (t_true);
        return (t_false);
    }
    else if (!delta_y)
    {
        if ((fabs(seg.y1 - mouse.y) <= 5) && ((mouse.x <= seg.x1
            && mouse.x >= seg.x2) || (mouse.x <= seg.x2 && mouse.x >= seg.x1)))
            return (t_true);
        return (t_false);
    }
    return (t_false);

}

enum e_bool     is_on_seg(t_segment seg, int mouse_x, int mouse_y)
{
    double  d;
    double  m;
    double  delta_x;
    double  delta_y;

    seg = transform_seg_in_ed_coords(seg);
    delta_x = seg.x2 - seg.x1;
    delta_y = seg.y2 - seg.y1;
    if (check_delta(delta_x, delta_y, seg, (t_i_coords){mouse_x, mouse_y}))
            return (t_true);
    if (!delta_x || !delta_y)
        return (t_false);
    m = delta_y / delta_x;
    d = -(m * seg.x1) + seg.y1;
    if (fabs(mouse_y - (m * mouse_x + d)) <= 10)
        return (t_true);
    return (t_false);
}

void    mouseup_action(t_editor *ed, int mouse_x, int mouse_y)
{
    (void)mouse_x; (void)mouse_y;
    if (ed->selected_nodes)
        free_walls_nodes(ed->selected_nodes);
    ed->selected_nodes = NULL;
    ed->selected_player = NULL;
    ed->selected_enemy = NULL;
    ed->selected_object = NULL;
}

void    mousedown_action(t_editor *ed, int mouse_x, int mouse_y)
{
    int count;
    t_linked_walls *linked_walls;

    if (click_on_panel(ed, &ed->buttons, mouse_x, mouse_y))
        return ;
    if (click_on_player(ed, ed->map, mouse_x, mouse_y))
        return ;
    if (click_on_enemy(ed, ed->map, mouse_x, mouse_y))
        return ;
    if (click_on_object(ed, ed->map, mouse_x, mouse_y))
    	return ;
    create_linked_walls_from_sectors(ed->map->sectors, &linked_walls, &count);
    if (click_on_nodes(ed, linked_walls, mouse_x, mouse_y))
        return ;
    if (click_on_walls(ed, linked_walls, mouse_x, mouse_y))
        return ;
    free_linked_walls_nodes(linked_walls);
}