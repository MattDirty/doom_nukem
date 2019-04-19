/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_which_sector.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badhont <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 06:07:54 by badhont           #+#    #+#             */
/*   Updated: 2019/04/19 06:08:18 by badhont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IN_WHICH_SECTOR_H
# define IN_WHICH_SECTOR_H

# include "sectors.h"

int			is_in_sector(t_coords pos, t_sector *sector);
t_sector	*in_which_sector(t_coords pos, t_sectors *sectors);
void		rotate_segment_around_first_extremity(t_segment *segment,
				const double angle);
enum e_bool	line_through_segment_intersects_a_sector_vertex(t_segment segment,
				t_sector *sector);

#endif
