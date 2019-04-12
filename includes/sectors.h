/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sectors.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfatton <lfatton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 05:50:47 by lfatton           #+#    #+#             */
/*   Updated: 2019/04/12 05:50:51 by lfatton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SECTORS_H
# define SECTORS_H

# include "textures.h"
# include "walls.h"
# include "objects.h"
# include "enemies.h"

typedef	struct			s_sector
{
    t_walls			    *walls;
    SDL_Surface         *floor;
    SDL_Surface         *ceil;
    enum e_bool         open_sky;
    Uint32				light;
    t_objects           *objects;
    t_enemies           *enemies;
}						t_sector;

typedef struct			s_sectors
{
    int					count;
    t_sector			 *items;
}						t_sectors;

void		free_sectors(t_sectors *sectors);
void		read_sectors_from_file(
        int fd,
        t_textures *textures,
        t_sectors **sectors);
void		write_sectors_to_file(int fd, t_sectors *sectors);

int		sector_index(t_sectors *sectors, t_sector *sector);

#endif
