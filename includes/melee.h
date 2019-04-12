#ifndef MELEE_H
# define MELEE_H

t_weapon    *load_melee(t_map *map);
void        melee_primary(t_player *player, t_timer_handler *timer_handler);

#endif
