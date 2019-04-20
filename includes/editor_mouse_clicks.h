#ifndef EDITOR_MOUSE_CLICKS_H
# define EDITOR_MOUSE_CLICKS_H

#include "editor.h"
#include "editor_draw.h"

enum e_bool	click_on_panel(t_editor *ed, int mouse_x, int mouse_y);
enum e_bool	click_on_nodes(t_editor *ed, t_linked_walls *linked_walls, int mouse_x, int mouse_y);
enum e_bool	click_on_player(t_editor *ed, t_map *map, int mouse_x, int mouse_y);
enum e_bool	click_on_walls(t_editor *ed, t_linked_walls *linked_walls, int mouse_x, int mouse_y);
enum e_bool	click_on_enemy(t_editor *ed, t_map *map, int mouse_x, int mouse_y);
enum e_bool	click_on_pickable(t_editor *ed, t_map *map, int mouse_x, int mouse_y);
enum e_bool	click_on_object(t_editor *ed, t_map *map, int mouse_x, int mouse_y);
enum e_bool	click_on_sector(t_editor *ed, t_map *map, int mouse_x, int mouse_y);
enum e_bool	is_on_seg(t_segment seg, t_i_coords mouse, t_i_coords map_offset, int zoom);
void		deal_with_clicked_player(t_editor *ed, t_coords *spawn);
void		deal_with_clicked_enemy(t_editor *ed, t_enemy *enemy);
void		deal_with_clicked_pickable(t_editor *ed, t_pickable *pickable);
void		deal_with_clicked_object(t_editor *ed, t_object *object);
void		deal_with_clicked_sector(t_editor *ed);
void		deal_with_clicked_node(t_editor *ed, t_linked_walls *linked, t_coords point);
void		clear_selection(t_selected_elements *selected);
void		copy_sector_floor_ceil(t_sector *target, t_sector *source);

#endif
