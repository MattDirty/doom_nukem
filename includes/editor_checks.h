#ifndef EDITOR_CHECKS_H
# define EDITOR_CHECKS_H

enum e_bool segment_intersect_with_map(t_linked_walls *walls, t_segment seg);
enum e_bool	new_node_pos_valid(t_editor *ed, t_coords pos);
enum e_bool	is_map_valid(t_linked_walls *walls, t_map *map);
enum e_bool	walls_intersect_on_map(t_linked_walls *linked_walls);

#endif
