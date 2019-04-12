#include "weapon.h"
#include "doom.h"
#include <SDL_mixer.h>
#include "melee.h"
#include "gun.h"
#include "map.h"

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
