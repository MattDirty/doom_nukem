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

typedef struct          s_collision
{
    double              distance;
    double              wall_length;
    t_coords            inters;
    t_wall				*wall;
}                       t_collision;

enum e_bool	check_collision(t_sector *sector, t_segment *seg, t_collision *collision);

#endif
