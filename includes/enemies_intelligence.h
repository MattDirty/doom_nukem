#ifndef DOOMNUKEM_ENEMIES_INTELLIGENCE_H
# define DOOMNUKEM_ENEMIES_INTELLIGENCE_H

# include "e_bool.h"
# include "timer_handler.h"

typedef struct s_env t_env;
typedef struct s_sector t_sector;
typedef struct s_enemy t_enemy;
typedef void (*t_enemy_intelligence)(
        t_enemy *enemy,
        t_sector *enemy_sector,
        t_env *e,
        double ms_since_update);

void			enemy_move(
        t_enemy *enemy,
        t_sector *enemy_sector,
        t_env *e,
        double time);
void			boss_intelligence(
        t_enemy *enemy,
        t_sector *enemy_sector,
        t_env *e,
        double ms_since_update);
enum e_bool     let_enemies_act(double ms_since_update, t_params params);

#endif
