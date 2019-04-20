/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badhont <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 11:49:35 by badhont           #+#    #+#             */
/*   Updated: 2019/04/19 11:57:56 by badhont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WALLS_H
# define WALLS_H

# include <SDL.h>
# include "utils.h"
# include "e_bool.h"
# include "textures.h"
# include "levers.h"
# include "wall_objects.h"

typedef struct s_sector		t_sector;
typedef struct s_sectors	t_sectors;

typedef struct				s_link
{
	t_sector				*sector1;
	t_sector				*sector2;
}							t_link;

enum						e_wall_type
{
	e_portal,
	e_wall,
	e_transparent_wall
};

typedef struct				s_wall
{
	t_segment				segment;
	enum e_wall_type		type;
	SDL_Surface				*texture;
	t_link					links;
	enum e_bool				to_infinity;
	double					wall_offset;
	t_wall_object			*wall_object;
	t_lever					*lever;
}							t_wall;

typedef struct				s_walls
{
	int						count;
	t_wall					**items;
}							t_walls;

typedef struct				s_linked_walls
{
	t_wall					*wall;
	struct s_linked_walls	*next;
}							t_linked_walls;

t_wall						*create_wall_copy(t_wall *wall);
void						add_wall_to_sector(t_sector *sector,
								t_wall *wall);
void						transform_wall_to_portal(t_wall *wall,
								t_sector *s1, t_sector *s2);
void						transform_wall_to_window(t_wall *wall,
								t_sector *sector);
void						transform_window_to_wall(t_wall *wall);
void						transform_portal_to_door(t_wall *wall,
								SDL_Surface *texture);
void						transform_door_to_portal(t_wall *wall,
								t_linked_walls *node);

int							wall_index(t_linked_walls *linked_walls,
								t_wall *wall);
t_wall						*wall_at_index(t_linked_walls *linked_walls,
								int index);
void						create_linked_walls_from_sectors(
							t_sectors *sectors,
							t_linked_walls **linked_walls,
							int *count);
void						free_linked_walls(t_linked_walls *linked_walls);
void						free_linked_walls_nodes(t_linked_walls
								*linked_walls);

void						free_linked_walls(
								t_linked_walls *linked_walls);
void						free_linked_walls_nodes(
								t_linked_walls *linked_walls);

int							wall_index(t_linked_walls *linked_walls,
								t_wall *wall);

void						read_linked_walls_from_file(
							int fd,
							t_sectors *sectors,
							t_textures *textures,
							t_linked_walls **linked_walls);

void						write_linked_walls_to_file(
							int fd,
							t_sectors *sectors,
							t_linked_walls **p_linked_walls);

void						read_walls_from_file(
							int fd,
							t_linked_walls *linked_walls,
							t_walls **walls);

void						write_walls_to_file(
							int fd,
							t_linked_walls *linked_walls,
							t_walls *walls);

void						read_wall_from_file(
							int fd,
							t_sectors *sectors,
							t_textures *textures,
							t_wall **wall);

void						write_wall_to_file(
							int fd,
							t_sectors *sectors,
							t_linked_walls *linked_walls,
							t_wall *wall);

#endif
