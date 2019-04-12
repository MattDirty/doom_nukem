#ifndef DOOMNUKEM_LEVERS_H
# define DOOMNUKEM_LEVERS_H

# include "SDL.h"

# include "wall_objects.h"
# include "e_bool.h"

typedef struct s_linked_walls t_linked_walls;
typedef struct s_wall t_wall;

typedef struct	s_lever
{
    t_wall_object	*wall_object;
    enum e_bool		activated;
    SDL_Surface		*up_texture;
    SDL_Surface		*down_texture;
    int				door_index;
    t_wall			*door;
}				t_lever;

typedef struct	s_door_animation
{
    t_wall			*door;
    double			elapsed_time;
    double			total_time;
    double			target_offset;
}				t_door_animation;

void	read_lever_from_file(
        int fd,
        t_textures *textures,
        t_lever **lever);
void	write_lever_to_file(
        int fd,
        t_linked_walls *linked_walls,
        t_lever *lever);

#endif
