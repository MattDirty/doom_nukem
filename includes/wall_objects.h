/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_objects.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badhont <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 10:22:30 by badhont           #+#    #+#             */
/*   Updated: 2019/04/19 10:24:35 by badhont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOOMNUKEM_WALL_OBJECTS_H
# define DOOMNUKEM_WALL_OBJECTS_H

# include <SDL.h>

# include "textures.h"

typedef struct		s_wall_object
{
	double			offset_on_wall;
	double			z;
	double			size;
	SDL_Surface		*texture;
}					t_wall_object;

void				read_wall_object_from_file(int fd, t_textures *textures,
						t_wall_object **wall_object);
void				write_wall_object_to_file(int fd,
						t_wall_object *wall_object);


t_wall_object   *create_wall_object(t_textures *textures);

#endif
