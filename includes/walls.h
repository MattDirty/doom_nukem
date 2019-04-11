#ifndef DOOMNUKEM_WALLS_H
# define DOOMNUKEM_WALLS_H

# include "SDL.h"
# include "utils.h"
# include "e_bool.h"
# include "textures.h"

typedef struct s_sector t_sector;
typedef struct s_sectors t_sectors;

typedef struct  s_link
{
    t_sector    *sector1;
    t_sector    *sector2;
}               t_link;

enum            e_wall_type
{
    e_portal,
    e_wall
};

union   u_pointer
{
    SDL_Surface *texture;
    t_link      sector;
};

typedef struct			s_wall
{
    t_segment			segment;
    union u_pointer     pointer;
    enum e_wall_type    type;
}						t_wall;

typedef struct			s_walls
{
    int					count;
    t_wall				**items;
}						t_walls;

typedef struct			s_linked_walls
{
    t_wall				*wall;
    struct s_linked_walls	*next;  // I'm not "fixing" the whole file, fuck the norm
}						t_linked_walls;

void			read_linked_walls_from_file(
        int fd,
        t_sectors *sectors,
        t_textures *textures,
        t_linked_walls **linked_walls);
void			write_linked_walls_to_file(
        int fd,
        t_sectors *sectors,
        t_linked_walls **p_linked_walls);

void			read_walls_from_file(
        int fd,
        t_linked_walls *linked_walls,
        t_walls **walls);
void			write_walls_to_file(
        int fd,
        t_linked_walls *linked_walls,
        t_walls *walls);

void			read_wall_from_file(
        int fd,
        t_sectors *sectors,
        t_textures *textures,
        t_wall **wall);
void			write_wall_to_file(
        int fd,
        t_sectors *sectors,
        t_wall *wall);

#endif
