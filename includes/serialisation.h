/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serialisation.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badhont <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 09:13:18 by badhont           #+#    #+#             */
/*   Updated: 2019/04/19 09:20:25 by badhont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOOMNUKEM_SERIALISATION_H
# define DOOMNUKEM_SERIALISATION_H
# include <unistd.h>

# include "textures.h"
# include "map.h"
# include "fonts.h"
# include "sounds.h"
# include "doom.h"

typedef struct		s_read_data
{
	t_textures		**textures;
	t_map			**map;
	t_fonts			**fonts;
	t_sounds		**sounds;
}					t_read_data;

void				read_file(char *filename, t_env *e);
void				read_file_editor(char *filename, t_read_data *e);
void				write_file(char *filename, t_textures *textures,
						t_map *map);

void				read_str_from_file(int fd, char **name);
void				write_str_to_file(int fd, char *name);

void				copy_file_in_file(int fd, char *name);
void				create_tmp_file_from_file(int fd, char *name);

#endif
