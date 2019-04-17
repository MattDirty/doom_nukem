#ifndef PICKABLES_H
# define PICKABLES_H

# include "SDL.h"

# include "textures.h"
# include "utils.h"
# include "objects.h"
# include "e_bool.h"
# include "timer_handler.h"
# include "sectors.h"

typedef struct s_weapon t_weapon;

typedef struct s_pickable
{
    t_object    *object;
    t_weapon    *weapon;
    enum pickable_type
    {
        basic_gun,
        shotgun
    }			type;
}               t_pickable;

typedef struct	        s_pickables
{
    t_pickable           item;
    struct s_pickables   *next;                                 
}		        t_pickables;

void free_pickables(t_pickables *pickables);
void read_pickables_from_file(
        int fd,
        t_textures *textures,
        t_pickables **pickables);
void write_pickables_to_file(int fd, t_pickables *pickables);

void read_pickable_from_file(int fd, t_textures *textures, t_pickable *pickable);
void write_pickable_to_file(int fd, t_pickable pickable);

void damage_pickable(t_timer_handler *timer_handler, t_pickable *pickable, Uint32 damage);
void	add_pickable(
        t_pickables **pickables,
        t_pickables *pickable);
t_pickables	*extract_pickable(
        t_pickables **pickables,
        t_pickable *pickable);
void	delete_pickable(
        t_pickables **pickables,
        t_pickable *pickable);

#endif
