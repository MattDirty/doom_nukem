#ifndef GUN_H
# define GUN_H

# include "sounds.h"

t_weapon    *load_gun(t_sounds *sounds, t_map *map);
enum e_bool gun_idle_anim(double ms_since_update, t_params params);

#endif
