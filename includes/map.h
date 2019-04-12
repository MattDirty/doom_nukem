/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfatton <lfatton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 05:49:36 by lfatton           #+#    #+#             */
/*   Updated: 2019/04/12 05:49:43 by lfatton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOOMNUKEM_MAP_H
# define DOOMNUKEM_MAP_H

# include "sectors.h"

typedef struct          s_hud
{
    SDL_Surface         *sun;
    SDL_Surface         *moon;
    SDL_Surface         *cross[3];
    int                 id;
    SDL_Surface         *bullet;
    SDL_Surface         *happy_face;
    SDL_Surface         *meh_face;
    SDL_Surface         *sad_face;
    SDL_Surface         *dead_face;
    SDL_Surface         *badass_face;
    SDL_Surface         *sehr_happy_face;
    SDL_Surface         *hurt_face;
}                       t_hud;

typedef struct			s_map
{
    t_sectors			*sectors;
    SDL_Surface         *daysky;
    SDL_Surface         *nightsky;
    enum e_bool         daytime;
    t_hud               hud;
}						t_map;

void		free_map(t_map *map);
void		read_map_from_file(int fd, t_textures *textures, t_map **map);
void		write_map_to_file(int fd, t_map *map);

#endif
