#include  "basic_enemies_intelligence.h"
#include "doom.h"
#include "enemies_intelligence.h"
#include "timer_handler.h"

enum e_bool	change_direction(double ms_since_update, t_params params)
{
    t_enemy	*enemy;

    printf("change_direction in\n");
    (void)ms_since_update;
    enemy = (t_enemy*)params;
    if (enemy->act == &fire)
        return (t_false);
    enemy->heading = (t_vector){rand() % 101 - 51, rand() % 101 - 51};
    if (enemy->heading.x == 0 && enemy->heading.y == 0)
        enemy->heading.x = 1;
    normalize_vector(&enemy->heading);
    printf("change_direction out\n");
    return (t_true);
}

enum e_bool	set_value(double ms_since_update, t_params params)
{
    printf("set_value in \n");
    t_set_value_data	*data;

    (void)ms_since_update;
    data = (t_set_value_data*)params;
    *((double*)data->p) = *((double*)data->value);
    free(data);
    printf("set_value out\n");
    return (t_false);
}

void	delayed_set_value(
        t_timer_handler *timer_handler,
        double delay,
        void *p,
        void *value)
{
    printf("delayed_set_value in\n");
    t_set_value_data	*data;

    if (!(data = (t_set_value_data*)malloc(sizeof(*data))))
        error_doom("oh no the memory is gone");
    data->p = p;
    data->value = value;
    add_event(timer_handler, delay, &set_value, data);
    printf("delayed_set_value out\n");
}

enum e_bool	pew(double ms_since_update, t_params params)
{
    t_pew_data	*data;
    SDL_Surface	*sprite;
    t_env		*e;

    (void)ms_since_update;
    data = (t_pew_data*)params;
    e = data->e;
    find_texture_by_name(e->textures, 
            "textures/sprites/enemy_front_firing_0.bmp", &sprite);
    data->enemy->front = sprite;
    find_texture_by_name(e->textures, 
            "textures/sprites/enemy_front_firing_1.bmp", &sprite);
    delayed_set_value(&e->timer_handler, 150, &data->enemy->front, &sprite);
    find_texture_by_name(e->textures, 
            "textures/sprites/enemy_front_firing_2.bmp", &sprite);
    delayed_set_value(&e->timer_handler, 200, &data->enemy->front, &sprite);
    find_texture_by_name(e->textures, 
            "textures/sprites/enemy_front_firing_3.bmp", &sprite);
    delayed_set_value(&e->timer_handler, 250, &data->enemy->front, &sprite);
    find_texture_by_name(e->textures, 
            "textures/sprites/enemy_front.bmp", &sprite);
    delayed_set_value(&e->timer_handler, 500, &data->enemy->front, &sprite);
    //todo #9 actually do some damage
    data->shots++;
    if (data->shots == 2)
    {
        free(data);
        return (t_false);
    }
    return (t_true);
}

void	roam(t_enemy *enemy, t_sector *enemy_sector, t_env *e)
{
    t_vector	to_player;
    t_pew_data	*data;
    static const double	speedy = .5;
    static const double	speed = .1;

    (void)enemy_sector;
    //enemy_move(
    //        enemy,
    //        (t_coords){
    //            enemy->object->x + enemy->heading.x,
    //            enemy->object->y + enemy->heading.y},
    //        enemy_sector,
    //        e);
    to_player = (t_vector){
            e->p.pos.x - enemy->object->x,
            e->p.pos.y - enemy->object->y};
    normalize_vector(&to_player);
    if (dot_product(&enemy->heading, &to_player) < COS_PI_EIGTH)
    {
        if (!(data = (t_pew_data*)malloc(sizeof(t_pew_data))))
            error_doom("pewpewpew");
        data->shots = 0;
        data->e = e;
        data->enemy = enemy;
        add_event(&e->timer_handler, 500, &pew, data);
        enemy->act = &fire;
        delayed_set_value(&e->timer_handler, 2000,
                &enemy->act, (void*)&flee);
        delayed_set_value(&e->timer_handler, 2000,
                &enemy->speed, (void*)&speedy);
        delayed_set_value(&e->timer_handler, 7000,
                &enemy->speed, (void*)&speed);
        delayed_set_value(&e->timer_handler, 7000,
                &enemy->act, (void*)&roam);
    }
}

void	fire(t_enemy *enemy, t_sector *enemy_sector, t_env *e)
{
    t_vector    to_player;

    (void)enemy_sector;
    to_player = (t_vector){
            e->p.pos.x - enemy->object->x,
            e->p.pos.y - enemy->object->y};
    normalize_vector(&to_player);
    enemy->heading = to_player;
}

void	flee(t_enemy *enemy, t_sector *enemy_sector, t_env *e)
{
    enemy_move(
            enemy,
            (t_coords){
                enemy->object->x + enemy->heading.x,
                enemy->object->y + enemy->heading.y},
            enemy_sector,
            e);
}

