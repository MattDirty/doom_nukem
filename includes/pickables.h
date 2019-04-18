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
typedef struct s_player t_player;
typedef struct s_object t_object;

typedef struct s_pickable
{
    t_object    *object;
    enum pickable_type
    {
        gun,
        shotgun,
        vacuum
    }			type;
}               t_pickable;

typedef struct	        s_pickables
{
    t_pickable           *item;
    struct s_pickables   *next;                                 
}		        t_pickables;

void    pick_objects(t_player *player);
//void free_pickables(t_pickables *pickables);

void write_pickables_to_file(int fd, t_pickables *pickables);
void write_pickable_to_file(int fd, t_pickable pickable);

void read_pickables_from_file(int fd, t_textures *textures, t_pickables **pickables);
void read_pickable_from_file(int fd, t_textures *textures, t_pickable *pickable);

/*void	add_pickable(
        t_pickables **pickables,
        t_pickables *pickable);*/
/*t_pickables	*extract_pickable(
        t_pickables **pickables,
        t_pickable *pickable);*/
void	delete_pickable(t_pickables *pickables, t_pickable *to_delete);

#endif
