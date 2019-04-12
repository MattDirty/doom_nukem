#include "weapon.h"
#include "doom.h"
#include <SDL_mixer.h>
#include "melee.h"
#include "gun.h"
#include "map.h"

void    weapon_ray_fire(t_player *p)
{
    t_weapon    *weapon;
    t_vector    vector;

    weapon = p->weapon;
    add_vector_to_vector(&vector, create_vector(cos(p->heading), -sin(p->heading)));

}

enum e_bool    unlock(double ms_since_update, t_params ready)
{
    (void)ms_since_update;
    *(enum e_bool*)ready = t_true;
    return (t_false);
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

t_weapons   *allocate_weapons(t_map *map)
{
    t_weapons   *node;
    t_weapons   *first;

    if (!(node = (t_weapons *)malloc(sizeof(t_weapons))))
        error_doom("Couldn't allocate weapons");
    first = node;
    node->item = load_melee(map);
    if (!(node->next = (t_weapons *)malloc(sizeof(t_weapons))))
        error_doom("Couldn't allocate weapons");
    node = node->next;
    node->next = NULL;
    node->item = load_gun(map);
    return (first);
}
