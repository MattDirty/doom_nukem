#include "e_bool.h"
#include "editor.h"
#include "editor_draw.h"
#include "editor_walls_nodes.h"
#include "editor_mouse_clicks.h"
#include "editor_panel_buttons.h"
#include "map.h"

t_segment       transform_seg_in_ed_coords(t_segment seg, t_i_coords map_offset, int zoom)
{
    seg.x1 = map_offset.x + seg.x1 * zoom;
    seg.x2 = map_offset.x + seg.x2 * zoom;
    seg.y1 = map_offset.y - seg.y1 * zoom;
    seg.y2 = map_offset.y - seg.y2 * zoom;
    return(seg);
}

enum e_bool     check_delta(double delta_x, double delta_y, t_segment seg, t_i_coords mouse)
{
    if (fabs(delta_x) <= 5)
        return ((fabs(seg.x1 - mouse.x) <= 8) && ((mouse.y <= seg.y1
            && mouse.y >= seg.y2) || (mouse.y <= seg.y2 && mouse.y >= seg.y1)));
    else if (fabs(delta_y) <= 5)
		return ((fabs(seg.y1 - mouse.y) <= 8) && ((mouse.x <= seg.x1
            && mouse.x >= seg.x2) || (mouse.x <= seg.x2 && mouse.x >= seg.x1)));
    return (e_false);

}

enum e_bool     is_on_seg(t_segment seg, t_i_coords mouse, t_i_coords map_offset, int zoom)
{
    double  d;
    double  m;
    double  delta_x;
    double  delta_y;

    seg = transform_seg_in_ed_coords(seg, map_offset, zoom);
    delta_x = seg.x2 - seg.x1;
    delta_y = seg.y2 - seg.y1;
    if (check_delta(delta_x, delta_y, seg, mouse))
            return (e_true);
    if (!delta_x || !delta_y)
        return (e_false);
    m = delta_y / delta_x;
    d = -(m * seg.x1) + seg.y1;
    if (fabs(mouse.y - (m * mouse.x + d)) <= 5)
        return (e_true);
    return (e_false);
}

void    mouseup_action(t_editor *ed, int mouse_x, int mouse_y)
{
    (void)mouse_x;
    (void)mouse_y;
    clear_selection(&ed->dragged);
}

void    mousedown_action(t_editor *ed, int mouse_x, int mouse_y)
{
    if (click_on_panel(ed, mouse_x, mouse_y))
        return ;
    clear_selection(&ed->selected);
    free_buttons_list(ed->panel.buttons);
    ed->panel.buttons = NULL;
    clear_selection(&ed->dragged);
    if (click_on_player(ed, ed->map, mouse_x, mouse_y))
        return ;
    if (click_on_enemy(ed, ed->map, mouse_x, mouse_y))
        return ;
    if (click_on_object(ed, ed->map, mouse_x, mouse_y))
    	return ;
    if (click_on_nodes(ed, ed->linked_walls, mouse_x, mouse_y))
        return ;
    if (click_on_walls(ed, ed->linked_walls, mouse_x, mouse_y))
        return ;
	if (click_on_sector(ed, ed->map, mouse_x, mouse_y))
		return ;
}