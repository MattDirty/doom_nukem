#ifndef EDITOR_STATES_H
# define EDITOR_STATES_H

#include "timer_handler.h"

void	new_sector_state(t_params params);
void	create_enemy_in_map_state(t_params params);
void	create_object_in_map_state(t_params params);
void	create_pickable_in_map_state(t_params params);
void	add_lever_state(t_params params);

#endif
