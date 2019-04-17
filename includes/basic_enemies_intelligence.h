#ifndef DOOMNUKEM_BASIC_ENEMIES_INTELLIGENCE_H
# define DOOMNUKEM_BASIC_ENEMIES_INTELLIGENCE_H

# include "enemies.h"

void	roam(
        t_enemy *enemy,
        t_sector *enemy_sector,
        t_env *e,
        double ms_since_update);
void	fire(
        t_enemy *enemy,
        t_sector *enemy_sector,
        t_env *e,
        double ms_since_update);
void	flee(
        t_enemy *enemy,
        t_sector *enemy_sector,
        t_env *e,
        double ms_since_update);

#endif
