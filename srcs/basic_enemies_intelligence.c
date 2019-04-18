#include  "basic_enemies_intelligence.h"
#include "doom.h"
#include "enemies_intelligence.h"
#include "player.h"

void	change_direction(t_enemy *enemy)
{
    enemy->heading = (t_vector){rand() % 101 - 51, rand() % 101 - 51};
    if (enemy->heading.x == 0 && enemy->heading.y == 0)
        enemy->heading.x = 1;
    normalize_vector(&enemy->heading);
}

static void	set_sprite(t_enemy *enemy, char *name, t_env *e)
{
    SDL_Surface *sprite;

    find_texture_by_name(e->textures, name, &sprite);
    enemy->front = sprite;
}

void	shoot_player(t_env *e, t_enemy *enemy)
{
    int i;
    int j;
    t_sector sector;
    t_segment segment;

    segment = (t_segment){enemy->object->x, enemy->object->y,
            e->p.pos.x, e->p.pos.y};
    j = 0;
    while (j < e->map->sectors->count)
    {
        sector = *e->map->sectors->items[j];
        i = 0;
        while (i < sector.walls->count)
        {
            if (sector.walls->items[i]->type == e_wall &&
                segments_intersect(
                    &segment,
                    &sector.walls->items[i]->segment,
                    &(t_coords){0, 0}))
                return;
            i++;
        }
        j++;
    }
    if (!e->p.success)
        e->p.health -= BRAZILIAN_HANDGUN_DAMAGE;
}

void	pew_part_two_yay_to_the_norm(t_enemy *enemy, t_env *e)
{
    if ((enemy->step == 3 && enemy->animation_time > 1500)
        || (enemy->step == 7 && enemy->animation_time > 2500)
        || (enemy->step == 11 && enemy->animation_time > 3500))
    {
        set_sprite(enemy, "textures/sprites/enemy_front_firing_3.bmp", e);
        enemy->step++;
    }
}

void	pew(t_enemy *enemy, t_env *e)
{
    if ((enemy->step == 0 && enemy->animation_time > 1000)
        || (enemy->step == 4 && enemy->animation_time > 2000)
        || (enemy->step == 8 && enemy->animation_time > 3000))
    {
        set_sprite(enemy, "textures/sprites/enemy_front_firing_0.bmp", e);
        enemy->step++;
    }
    if ((enemy->step == 1 && enemy->animation_time > 1300)
        || (enemy->step == 5 && enemy->animation_time > 2300)
        || (enemy->step == 9 && enemy->animation_time > 3300))
    {
        set_sprite(enemy, "textures/sprites/enemy_front_firing_1.bmp", e);
        enemy->step++;
    }
    if ((enemy->step == 2 && enemy->animation_time > 1400)
        || (enemy->step == 6 && enemy->animation_time > 2400)
        || (enemy->step == 10 && enemy->animation_time > 3400))
    {
        set_sprite(enemy, "textures/sprites/enemy_front_firing_2.bmp", e);
        enemy->step++;
        shoot_player(e, enemy);
    }
    pew_part_two_yay_to_the_norm(enemy, e);
}

void	roam(
        t_enemy *enemy,
        t_sector *enemy_sector,
        t_env *e,
        double ms_since_update)
{
    t_vector	to_player;

    (void)enemy_sector;
    if (enemy->animation_time > 1000)
    {
        change_direction(enemy);
        enemy->animation_time = 0;
    }
    enemy_move(enemy, enemy_sector, e, ms_since_update);
    to_player = (t_vector){
            e->p.pos.x - enemy->object->x,
            e->p.pos.y - enemy->object->y};
    normalize_vector(&to_player);
    if (dot_product(&enemy->heading, &to_player) < COS_PI_FOURTH)
        return;
    enemy->animation_time = 0;
    enemy->step = 0;
    enemy->act = &fire;
    enemy->speed = FAST_SCOOTER_SPEED;
}

void	fire(
        t_enemy *enemy,
        t_sector *enemy_sector,
        t_env *e,
        double ms_since_update)
{
    t_vector    to_player;

    (void)ms_since_update;
    (void)enemy_sector;
    to_player = (t_vector){
            e->p.pos.x - enemy->object->x,
            e->p.pos.y - enemy->object->y};
    normalize_vector(&to_player);
    enemy->heading = to_player;
    pew(enemy, e);
    if (enemy->animation_time < 4000)
        return;
    enemy->animation_time = 0;
    enemy->step = 0;
    enemy->act = &flee;
    set_sprite(enemy, "textures/sprites/enemy_front.bmp", e);
}

void	flee(
        t_enemy *enemy,
        t_sector *enemy_sector,
        t_env *e,
        double ms_since_update)
{
    if (enemy->animation_time > 1000)
    {
        change_direction(enemy);
        enemy->animation_time = 0;
        enemy->step++;
    }
    enemy_move(enemy, enemy_sector, e, ms_since_update);
    if (enemy->step < 4)
        return;
    enemy->animation_time = 0;
    enemy->step = 0;
    enemy->act = &roam;
    enemy->speed = BASE_SCOOTER_SPEED;
}
