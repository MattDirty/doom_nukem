#ifndef DOOMNUKEM_BASIC_ENEMIES_INTELLIGENCE_H
# define DOOMNUKEM_BASIC_ENEMIES_INTELLIGENCE_H

# include "enemies.h"

typedef struct  s_pew_data
{
    t_enemy		*enemy;
    t_env		*e;
    int			shots;
}				t_pew_data;

typedef struct  s_set_value_data
{
    void		*p;
    void		*value;
}				t_set_value_data;

void	roam(t_enemy *enemy, t_sector *enemy_sector, t_env *e);
void	fire(t_enemy *enemy, t_sector *enemy_sector, t_env *e);
void	flee(t_enemy *enemy, t_sector *enemy_sector, t_env *e);

#endif
