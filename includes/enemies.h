/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemies.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfatton <lfatton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 05:49:03 by lfatton           #+#    #+#             */
/*   Updated: 2019/04/12 05:49:14 by lfatton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENEMIES_H
# define ENEMIES_H

# include "SDL.h"
# include "textures.h"
# include "utils.h"
# include "objects.h"

typedef struct s_enemy
{
    t_object    *object;
    Uint32      hp;
    double      heading;
    SDL_Surface *front;
    SDL_Surface *side;
}               t_enemy;

typedef struct  s_enemies
{
    t_enemy     *items;
    int         count;
}               t_enemies;

void free_enemies(t_enemies *enemies);
void read_enemies_from_file(int fd, t_textures *textures, t_enemies **enemies);
void write_enemies_to_file(int fd, t_enemies *enemies);

void read_enemy_from_file(int fd, t_textures *textures, t_enemy *enemy);
void write_enemy_to_file(int fd, t_enemy enemy);

#endif
