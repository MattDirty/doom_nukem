#include "default.h"
#include "player.h"
#include "enemies_intelligence.h"
#include "doom.h"
#include "enemies.h"
#include "utils.h"

void			enemy_move(t_enemy *enemy, t_coords d, t_env *e)
{
    (void)e;
    t_vector	direction;

    direction = (t_vector){d.x - enemy->object->x, d.y - enemy->object->y};
    normalize_vector(&direction);
    scalar_multiply(&direction, enemy->speed);
    enemy->object->x += direction.x;
    enemy->object->y += direction.y;
}

void			boss_intelligence(t_enemy *enemy, t_env *e)
{
    double		dist;
    double		ratio;

    dist = get_distance_between_points(
            e->p.pos.x, e->p.pos.y,
            enemy->object->x, enemy->object->y);
    ratio = dist / 2;
    e->p.health -= BLACKHOLE_AURA_DAMAGE / 60.0 / ratio;
    e->p.hurt = ratio <= 2.5;
    enemy_move(enemy, e->p.pos, e);
}

void			basic_enemy_intelligence(t_enemy *enemy, t_env *e)
{
    (void)e;
    enemy->object->z = 0.5;
}

enum e_bool     let_enemies_act(double ms_since_update, t_params params)
{
    t_env		*e;
    t_enemy		*enemy;
    int			i;
    int			j;

    (void)ms_since_update;
    e = (t_env*) params;
    i = 0;
    while  (i < e->map->sectors->count)
    {
        j = 0;
        while  (j < e->map->sectors->items[i].enemies->count)
        {
            enemy = &e->map->sectors->items[i].enemies->items[j];
            enemy->act(enemy, e);
            j++;
        }
        i++;
    }
    return (t_true);
}
