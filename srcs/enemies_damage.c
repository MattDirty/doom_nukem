/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemies_damage.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfatton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 05:01:09 by lfatton           #+#    #+#             */
/*   Updated: 2019/04/19 05:01:10 by lfatton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "basic_enemies_intelligence.h"
#include "e_bool.h"
#include "sectors.h"
#include "doom.h"

t_linked_enemies	*extract_enemy(t_linked_enemies **linked_enemies,
		t_enemy *enemy)
{
	t_linked_enemies	*previous;
	t_linked_enemies	*n;

	if (enemy == &(*linked_enemies)->item)
	{
		previous = *linked_enemies;
		*linked_enemies = previous->next;
		previous->next = NULL;
		return (previous);
	}
	previous = NULL;
	n = *linked_enemies;
	while (n)
	{
		if (&n->item == enemy)
		{
			previous->next = n->next;
			n->next = NULL;
			return (n);
		}
		previous = n;
		n = n->next;
	}
	return (NULL);
}

void				delete_enemy(t_linked_enemies **linked_enemies,
		t_enemy *enemy)
{
	t_linked_enemies	*n;

	n = extract_enemy(linked_enemies, enemy);
	if (!n)
		return ;
	free(n->item.object);
	free(n);
}

enum e_bool			enemy_death(double ms_since_update, t_params params)
{
	t_enemy	*enemy;
	int		step;

	enemy = (t_enemy *)params;
	enemy->time_in_death += ms_since_update;
	step = (int)(enemy->time_in_death) / (int)(enemy->death_duration / 16);
	if (step >= 16)
		step = 15;
	enemy->object->sprite = enemy->explosion[step];
	if (enemy->time_in_death >= enemy->death_duration)
	{
		enemy->to_destroy = e_true;
		return (e_false);
	}
	return (e_true);
}

void				damage_enemy(t_env *e, t_timer_handler *timer_handler,
		t_enemy *enemy, Uint32 damage)
{
	enemy->life_remaining -= damage;
	if (enemy->life_remaining <= 0 && (int)enemy->time_in_death <= 0)
	{
		if (enemy->type == et_boss)
		{
			Mix_PlayChannel(-1, e->sounds->yeee, 0);
			e->p.success = e_true;
			enemy->to_destroy = e_true;
		}
		else
		{
			Mix_PlayChannel(-1, e->sounds->xplosion, 0);
			enemy->death_duration = 1700;
			enemy->time_in_death = 1;
			add_event(timer_handler, 1, &enemy_death, enemy);
		}
	}
}
