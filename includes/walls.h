/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfatton <lfatton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 05:53:30 by lfatton           #+#    #+#             */
/*   Updated: 2019/04/12 05:53:45 by lfatton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WALLS_H
# define WALLS_H

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
    e_wall,
    e_transparent_wall
};

union   u_pointer
{
    SDL_Surface *texture;
    t_link      sector;
};

typedef struct			s_wall_object
{
    double				offset_on_wall;
    double				z;
    double				size;
    SDL_Surface			*texture;
}						t_wall_object;

typedef struct			s_wall
{
    t_segment			segment;
    enum e_wall_type    type;
    SDL_Surface         *texture;
    t_link              links;
    enum e_bool         to_infinity;
    t_wall_object		*wall_object;
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

void			create_linked_walls_from_sectors(
        t_sectors *sectors,
        t_linked_walls **linked_walls,
        int *count);
void	free_linked_walls(t_linked_walls *linked_walls);
void	free_linked_walls_nodes(t_linked_walls *linked_walls);

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

void			read_wall_object_from_file(
        int fd,
        t_textures *textures,
        t_wall_object **wall_object);
void			write_wall_object_to_file(
        int fd,
        t_wall_object *wall_object);

#endif
