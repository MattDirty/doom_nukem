/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfatton <lfatton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 05:49:49 by lfatton           #+#    #+#             */
/*   Updated: 2019/04/12 05:50:07 by lfatton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECTS_H
# define OBJECTS_H

# include "SDL.h"
# include "textures.h"
# include "utils.h"

typedef struct s_object
{
    double      x;
    double      y;
    double			z;
    double			horizontal_size;
    double			vertical_size;
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

void free_objects(t_objects *objects);
void read_objects_from_file(int fd, t_textures *textures, t_objects **objects);
void write_objects_to_file(int fd, t_objects *objects);

void read_object_from_file(int fd, t_textures *textures, t_object *object);
void write_object_to_file(int fd, t_object object);

#endif
