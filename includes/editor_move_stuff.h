#ifndef EDITOR_MOVE_STUFF_H
# define EDITOR_MOVE_STUFF_H

void    move_walls_nodes(t_wall_nodes *nodes, double x, double y);
void    move_player_spawn(t_coords *spawn, double x, double y);
void	move_enemy(t_enemy *enemy, double x, double y);

#endif