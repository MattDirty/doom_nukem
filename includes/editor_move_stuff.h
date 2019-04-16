#ifndef EDITOR_MOVE_STUFF_H
# define EDITOR_MOVE_STUFF_H

void    move_map(t_editor *ed, SDL_Scancode key);
void    move_walls_nodes(t_wall_nodes *nodes, double x, double y, int zoom);
void    move_player_spawn(t_coords *spawn, double x, double y, int zoom);
void	move_object(t_object *object, double x, double y, int zoom);

#endif