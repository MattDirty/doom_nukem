#ifndef EDITOR_MOVE_STUFF_H
# define EDITOR_MOVE_STUFF_H

void    move_map(t_editor *ed, SDL_Scancode key);
void    move_walls_nodes(t_editor *ed, double x, double y);
void    move_player_spawn(t_editor *ed, double x, double y);
void	move_object(t_editor *ed, double x, double y);
void	move_enemy(t_editor *ed, double x, double y);

#endif