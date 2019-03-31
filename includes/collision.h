/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtorsell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 01:25:21 by mtorsell          #+#    #+#             */
/*   Updated: 2019/03/30 01:25:26 by mtorsell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLLISION_H
# define COLLISION_H

# include "utils.h"
# include "walls.h"
# include "sectors.h"
# include "doom.h"

typedef struct          s_collision
{
    double              distance;
    t_coords            inters;
    t_wall				*wall;
}                       t_collision;

t_collision	check_collision(t_sector *sector, t_segment *seg);
void		raycasting(t_env *e);

#endif