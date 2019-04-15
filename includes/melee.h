#ifndef MELEE_H
# define MELEE_H

# include "sounds.h"

void        fuck_flower(t_player *p, t_object *object);
t_weapon    *load_melee(t_sounds *sounds, t_map *map);
void        melee_primary(t_player *player, t_timer_handler *timer_handler);

#endif
