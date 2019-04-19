/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_enemies_intelligence.h                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badhont <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 02:11:35 by badhont           #+#    #+#             */
/*   Updated: 2019/04/19 02:13:26 by badhont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOOMNUKEM_BASIC_ENEMIES_INTELLIGENCE_H
# define DOOMNUKEM_BASIC_ENEMIES_INTELLIGENCE_H

# include "enemies.h"

void	roam(t_enemy *enemy, t_sector *enemy_sector, t_env *e,
			double ms_since_update);
void	fire(t_enemy *enemy, t_sector *enemy_sector, t_env *e,
			double ms_since_update);
void	flee(t_enemy *enemy, t_sector *enemy_sector, t_env *e,
			double ms_since_update);
void	pew(t_enemy *enemy, t_env *e);
void	pew_part_two_yay_to_the_norm(t_enemy *enemy, t_env *e);
void	shoot_player(t_env *e, t_enemy *enemy);
void	change_direction(t_enemy *enemy);
void	set_sprite(t_enemy *enemy, char *name, t_env *e);

#endif
