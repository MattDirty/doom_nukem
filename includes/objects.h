#ifndef DOOM_NUKEM_OBJECTS_H
# define DOOM_NUKEM_OBJECTS_H

# include "SDL.h"

# include "textures.h"
# include "utils.h"
# include "e_bool.h"
# include "sectors.h"

typedef struct s_object
{
    double          x;
    double          y;
    double			z;
    double			horizontal_size;
    double			vertical_size;
    SDL_Surface     *sprite;
    enum e_bool     can_give_bonus;
}               t_object;

typedef struct  s_objects
{
    t_object    *items;
    int         count;
}               t_objects;

t_segment perpendicular_segment_from_point(
        t_object *object,
        double point_of_view_x,
        double point_of_view_y);

void free_objects(t_objects *objects);
void read_objects_from_file(int fd, t_textures *textures, t_objects **objects);
void write_objects_to_file(int fd, t_objects *objects);

void read_object_from_file(int fd, t_textures *textures, t_object *object);
void write_object_to_file(int fd, t_object object);

t_object    *add_new_object_to_sector_at_pos(
        t_sector *sector, t_coords pos, t_textures *textures);

#endif
