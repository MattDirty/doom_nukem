#ifndef DOOMNUKEM_LEVERS_H
# define DOOMNUKEM_LEVERS_H

typedef struct			s_wall_object
{
    double				offset_on_wall;
    double				z;
    double				size;
    SDL_Surface			*texture;
}						t_wall_object;

void			read_wall_object_from_file(
        int fd,
        t_textures *textures,
        t_wall_object **wall_object);
void			write_wall_object_to_file(
        int fd,
        t_wall_object *wall_object);

#endif
