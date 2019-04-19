/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gun.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badhont <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 06:06:45 by badhont           #+#    #+#             */
/*   Updated: 2019/04/19 06:07:03 by badhont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GUN_H
# define GUN_H

# include "sounds.h"

t_weapon	*load_gun(t_sounds *sounds, t_map *map);
t_weapon	*load_shotgun(t_sounds *sounds, t_map *map);
t_weapon	*load_vacuum(t_sounds *sounds, t_map *map);
enum e_bool gun_idle_anim(double ms_since_update, t_params params);

#endif
