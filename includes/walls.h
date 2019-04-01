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
    wtPortal,
    wtWall
};

union   u_pointer
{
    SDL_Surface *texture;
    t_link      sector;
};

typedef struct			s_wall
{
    t_segment			segment;
    double				height; //debug
    union u_pointer     pointer;
    enum e_wall_type    type;
}						t_wall;

typedef struct			s_walls
{
    int					count;
    t_wall				**items;
}						t_walls;

int			read_walls_from_file(
        int fd,
        t_sectors *sectors,
        t_textures *textures,
        t_walls **walls);
int			write_walls_to_file(int fd, t_sectors *sectors, t_walls *walls);

int			read_wall_from_file(
        int fd,
        t_sectors *sectors,
        t_textures *textures,
        t_wall **wall);
int			write_wall_to_file(
        int fd,
        t_sectors *sectors,
        t_wall *wall);

#endif
