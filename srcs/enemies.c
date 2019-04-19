#include <SDL_mixer.h>
#include "enemies.h"
#include "doom.h"

void	free_enemies(t_linked_enemies *enemies)
{
    if (!enemies)
        return;
    free_enemies(enemies->next);
    free(enemies->item.object);
    free(enemies);
}

void	add_enemy(
        t_linked_enemies **linked_enemies,
        t_linked_enemies *enemy)
{
    t_linked_enemies	*node;

    if (!*linked_enemies)
    {
        *linked_enemies = enemy;
        return;
    }
    node = *linked_enemies;
    while (node->next)
        node = node->next;
    node->next = enemy;
}
