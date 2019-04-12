#ifndef ENEMIES_H
# define ENEMIES_H

# include "SDL.h"

# include "textures.h"
# include "utils.h"
# include "objects.h"
# include "e_bool.h"
# include "timer_handler.h"

typedef struct s_enemy
{
    t_object    *object;
    int			life_remaining;
    double		death_duration;
    double		time_in_death;
    enum e_bool	to_destroy;
    double      heading;
    SDL_Surface *front;
    SDL_Surface *side;
}               t_enemy;

typedef struct  s_enemies
{
    t_enemy     *items;
    int         count;
}               t_enemies;

void free_enemies(t_enemies *enemies);
void read_enemies_from_file(int fd, t_textures *textures, t_enemies **enemies);
void write_enemies_to_file(int fd, t_enemies *enemies);

void read_enemy_from_file(int fd, t_textures *textures, t_enemy *enemy);
void write_enemy_to_file(int fd, t_enemy enemy);

void enemy_hit(t_timer_handler *timer_handler, t_enemy *enemy, Uint32 damage);

#endif
