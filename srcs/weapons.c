#include "weapon.h"
#include "doom.h"
#include <SDL_mixer.h>
#include "melee.h"
#include "gun.h"
#include "map.h"
#include "collision.h"

void    weapon_ray_fire(t_env *e, t_timer_handler *timer_handler)
{
    t_weapon        *weapon;
    t_ray           ray;
    t_collisions    *collisions;
    t_collisions    *ptr;
    Uint32          x;
    double          angle;

    weapon = e->p.weapon;
    x = -1;
    angle = e->p.heading - weapon->scatter_angle / 2;
    while (angle <= e->p.heading + weapon->scatter_angle / 2)
    {
        angle += weapon->scatter_angle / weapon->scatter;
        ray.angle = angle;
        ray.vect = create_vector(cos(ray.angle), -sin(ray.angle));
        change_vector_magnitude(&ray.vect, weapon->range);
        ray.seg = create_segment_from_position_and_vector(e->p.pos.x,
                e->p.pos.y, &ray.vect);
        find_ray_collisions(e->p.current_sector, &ray.seg, &collisions);
        if (!collisions)
            continue;
        ptr = collisions;
        while (ptr
        && ptr->item.type == ct_wall && ptr->item.d.wall->type == e_portal)
            ptr = ptr->next;
        if (ptr && ptr->item.type == ct_enemy)
			damage_enemy(e, timer_handler, ptr->item.d.enemy, weapon->damage);
        else if (ptr && ptr->item.type == ct_object && weapon->ammo == -1)
            fuck_flower(&e->p, ptr->item.d.object);
        free_collisions(collisions);
    }
}

enum e_bool    unlock(double ms_since_update, t_params ready)
{
    (void)ms_since_update;
    *(enum e_bool*)ready = e_true;
    return (e_false);
}

t_weapon    *get_weapon(t_weapons *node, Uint32 target)
{
    Uint32  i;

    i = 0;
    while (node && i < target)
    {
        node = node->next;
        i++;
    }
    return (node->item);
}

t_weapons   *allocate_weapons(t_sounds *sounds, t_map *map)
{
    t_weapons   *node;
    t_weapons   *first;

    if (!(node = (t_weapons *)malloc(sizeof(t_weapons))))
        error_doom("Couldn't allocate weapons");
    first = node;
    node->item = load_melee(sounds, map);
    if (!(node->next = (t_weapons *)malloc(sizeof(t_weapons))))
        error_doom("Couldn't allocate weapons");
    node = node->next;
    node->next = NULL;
    node->item = load_gun(sounds, map);
    if (!(node->next = (t_weapons *)malloc(sizeof(t_weapons))))
        error_doom("Couldn't allocate weapons");
    node = node->next;
    node->next = NULL;
    node->item = load_shotgun(sounds, map);
    if (!(node->next = (t_weapons *)malloc(sizeof(t_weapons))))
        error_doom("Couldn't allocate weapons");
    node = node->next;
    node->next = NULL;
    node->item = load_vacuum(sounds, map);
    return (first);
}

void		free_weapons(t_weapons *weapons)
{
    t_weapons	*n;
    t_weapons	*p;

    n = weapons;
    while (n)
    {
        if (n->item->sprites)
            free(n->item->sprites);
        if (n->item->sprites_fire)
            free(n->item->sprites_fire);
        if (n->item->sprites_cooldown)
            free(n->item->sprites_cooldown);
        free(n->item);
        p = n;
        n = n->next;
        free(p);
    }
}
