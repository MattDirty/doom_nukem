#ifndef ENEMIES_H
# define ENEMIES_H

# include "SDL.h"

# include "textures.h"
# include "utils.h"
# include "objects.h"
# include "e_bool.h"
# include "timer_handler.h"
# include "sectors.h"
# include "enemies_intelligence.h"

typedef struct s_object t_object;

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
    SDL_Surface *back;
    enum enemy_type
    {
        et_boss,
        et_brazil
    }			type;
    t_enemy_intelligence act;
    double		speed;
    SDL_Surface *explosion[16];
}               t_enemy;

typedef struct	s_linked_enemies
{
    t_enemy		item;
    struct s_linked_enemies	*next;
}				t_linked_enemies;

void free_enemies(t_linked_enemies *enemies);
void read_enemies_from_file(
        int fd,
        t_textures *textures,
        t_linked_enemies **enemies);
void write_enemies_to_file(int fd, t_linked_enemies *enemies);

void read_enemy_from_file(int fd, t_textures *textures, t_enemy *enemy);
void write_enemy_to_file(int fd, t_enemy enemy);

void damage_enemy(t_env *e,
        t_timer_handler *timer_handler, t_enemy *enemy, Uint32 damage);
void	add_enemy(
        t_linked_enemies **linked_enemies,
        t_linked_enemies *enemy);
t_linked_enemies	*extract_enemy(
        t_linked_enemies **linked_enemies,
        t_enemy *enemy);
void	delete_enemy(
        t_linked_enemies **linked_enemies,
        t_enemy *enemy);

#endif
