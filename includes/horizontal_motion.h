/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   horizontal_motion.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badhont <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 06:07:09 by badhont           #+#    #+#             */
/*   Updated: 2019/04/19 06:07:44 by badhont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOOMNUKEM_HORIZONTAL_MOTION_H
# define DOOMNUKEM_HORIZONTAL_MOTION_H

# include "utils.h"
# include "sectors.h"

t_coords	allowed_move(t_vector speed, t_coords position,
				t_sector **current_sector);

#endif
