#include "default.h"
#include "player.h"
#include "enemies_intelligence.h"
#include "doom.h"
#include "enemies.h"
#include "utils.h"
#include "in_which_sector.h"

void			enemy_move(
        t_enemy *enemy,
        t_coords d,
        t_sector *enemy_sector,
        t_env *e)
{
    t_vector	direction;
    t_linked_enemies	*extracted_node;
    t_sector	*new_sector;

    direction = (t_vector){d.x - enemy->object->x, d.y - enemy->object->y};
    normalize_vector(&direction);
    scalar_multiply(&direction, enemy->speed);
    enemy->object->x += direction.x;
    enemy->object->y += direction.y;
    if (!is_in_sector(
            (t_coords){enemy->object->x, enemy->object->y},
            enemy_sector))
    {
        new_sector = in_which_sector(
                (t_coords){enemy->object->x, enemy->object->y},
                e->map->sectors);
        if (!new_sector)
            return;
        extracted_node = extract_enemy(&enemy_sector->enemies, enemy);
        add_enemy(&new_sector->enemies, extracted_node);
    }
}

void			boss_intelligence(
        t_enemy *enemy,
        t_sector *enemy_sector,
        t_env *e)
{
    double		dist;
    double		ratio;

    dist = get_distance_between_points(
            e->p.pos.x, e->p.pos.y,
            enemy->object->x, enemy->object->y);
    ratio = dist / 2;
    e->p.health -= BLACKHOLE_AURA_DAMAGE / 60.0 / ratio;
    if (e->p.health <= 0)
        e->p.dead = e_true;
    e->p.hurt = ratio <= 2.5;
    enemy_move(enemy, e->p.pos, enemy_sector, e);
}

void			basic_enemy_intelligence(
        t_enemy *enemy,
        t_sector *enemy_sector,
        t_env *e)
{
    (void)e;
    (void)enemy_sector;
    enemy->object->z = 0.5;
}

enum e_bool     let_enemies_act(double ms_since_update, t_params params)
{
    t_env		*e;
    t_enemy		*enemy;
    int			i;
    t_linked_enemies	*node;
    t_sector	*sector;

    (void)ms_since_update;
    e = (t_env*) params;
    i = 0;
    while  (i < e->map->sectors->count)
    {
        sector = e->map->sectors->items + i;
        node = sector->enemies;
        while  (node)
        {
            enemy = &node->item;
            enemy->act(enemy, sector, e);
            node = node->next;
        }
        i++;
    }
    return (e_true);
}
