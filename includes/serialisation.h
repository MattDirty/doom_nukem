/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serialisation.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfatton <lfatton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 05:50:59 by lfatton           #+#    #+#             */
/*   Updated: 2019/04/12 05:51:15 by lfatton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERIALISATION_H
# define SERIALISATION_H

# include <unistd.h>
# include "textures.h"
# include "map.h"

void	read_file(char *filename, t_textures **textures, t_map **map);
void	write_file(char *filename, t_textures *textures, t_map *map);

void	read_str_from_file(int fd, char **name);
void	write_str_to_file(int fd, char *name);

#endif
