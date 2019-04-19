/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemies.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfatton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 07:09:41 by lfatton           #+#    #+#             */
/*   Updated: 2019/04/19 07:12:55 by lfatton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <SDL_mixer.h>
#include "enemies.h"
#include "doom.h"

void	free_enemies(t_linked_enemies *enemies)
{
	if (!enemies)
		return ;
	free_enemies(enemies->next);
	free(enemies->item.object);
	free(enemies);
}

void	add_enemy(t_linked_enemies **linked_enemies, t_linked_enemies *enemy)
{
	t_linked_enemies	*n;

	if (!*linked_enemies)
	{
		*linked_enemies = enemy;
		return ;
	}
	n = *linked_enemies;
	while (n->next)
		n = n->next;
	n->next = enemy;
}
