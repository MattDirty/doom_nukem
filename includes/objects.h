#ifndef DOOM_NUKEM_OBJECTS_H
# define DOOM_NUKEM_OBJECTS_H

# include "SDL.h"

# include "textures.h"
# include "utils.h"

typedef struct s_object
{
    double      x;
    double      y;
    SDL_Surface *sprite;
}               t_object;

typedef struct  s_objects
{
    t_object*   items;
    int         count;
}               t_objects;

t_segment perpendicular_segment_from_point(
        t_object *object,
        double point_of_view_x,
        double point_of_view_y);

int read_objects_from_file(int fd, t_textures *textures, t_objects **objects);
int write_objects_to_file(int fd, t_objects *objects);

int read_object_from_file(int fd, t_textures *textures, t_object *object);
int write_object_to_file(int fd, t_object object);

#endif
