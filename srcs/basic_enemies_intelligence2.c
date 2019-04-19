/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_enemies_intelligence2.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfatton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 05:48:46 by lfatton           #+#    #+#             */
/*   Updated: 2019/04/19 05:54:55 by lfatton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "basic_enemies_intelligence.h"
#include "doom.h"
#include "enemies_intelligence.h"
#include "player.h"

void		roam(t_enemy *enemy, t_sector *enemy_sector, t_env *e,
				double ms_since_update)
{
	t_vector	to_player;

	if (enemy->animation_time > 1000)
	{
		change_direction(enemy);
		enemy->animation_time = 0;
	}
	enemy_move(enemy, enemy_sector, e, ms_since_update);
	to_player = (t_vector){e->p.pos.x - enemy->object->x,
		e->p.pos.y - enemy->object->y};
	normalize_vector(&to_player);
	if (dot_product(&enemy->heading, &to_player) < COS_PI_FOURTH)
		return ;
	enemy->animation_time = 0;
	enemy->step = 0;
	enemy->act = &fire;
	enemy->speed = FAST_SCOOTER_SPEED;
}

void		fire(t_enemy *enemy, t_sector *enemy_sector, t_env *e,
				double ms_since_update)
{
	t_vector	to_player;

	(void)ms_since_update;
	(void)enemy_sector;
	to_player = (t_vector){e->p.pos.x - enemy->object->x,
		e->p.pos.y - enemy->object->y};
	normalize_vector(&to_player);
	enemy->heading = to_player;
	pew(enemy, e);
	if (enemy->animation_time < 4000)
		return ;
	enemy->animation_time = 0;
	enemy->step = 0;
	enemy->act = &flee;
	set_sprite(enemy, "textures/sprites/enemy_front.bmp", e);
}

void		flee(t_enemy *enemy, t_sector *enemy_sector, t_env *e,
				double ms_since_update)
{
	if (enemy->animation_time > 1000)
	{
		change_direction(enemy);
		enemy->animation_time = 0;
		enemy->step++;
	}
	enemy_move(enemy, enemy_sector, e, ms_since_update);
	if (enemy->step < 4)
		return ;
	enemy->animation_time = 0;
	enemy->step = 0;
	enemy->act = &roam;
	enemy->speed = BASE_SCOOTER_SPEED;
}
