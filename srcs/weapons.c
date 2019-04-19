/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapons.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtorsell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/20 00:14:32 by mtorsell          #+#    #+#             */
/*   Updated: 2019/04/20 00:14:34 by mtorsell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "collision.h"
#include "weapon.h"
#include "gun.h"
#include "melee.h"

enum e_bool	unlock(double ms_since_update, t_params ready)
{
	(void)ms_since_update;
	*(enum e_bool *)ready = e_true;
	return (e_false);
}

t_weapon	*get_weapon(t_weapons *node, Uint32 target)
{
	Uint32	i;

	i = 0;
	while (node && i < target)
	{
		node = node->next;
		i++;
	}
	return (node->item);
}

void		put_weapon(t_weapons *node, t_weapon *weapon, Uint32 target)
{
	Uint32	i;

	i = 0;
	while (node && i < target)
	{
		node = node->next;
		i++;
	}
	node->item = weapon;
}

t_weapons	*allocate_weapons(t_sounds *sounds, t_map *map)
{
	t_weapons	*node;
	t_weapons	*first;

	if (!(node = (t_weapons *)malloc(sizeof(t_weapons))))
		error_doom("Couldn't allocate weapons");
	first = node;
	node->item = load_melee(sounds, map);
	if (!(node->next = (t_weapons *)malloc(sizeof(t_weapons))))
		error_doom("Couldn't allocate weapons");
	node = node->next;
	node->next = NULL;
	node->item = load_gun(sounds, map);
	if (!(node->next = (t_weapons *)malloc(sizeof(t_weapons))))
		error_doom("Couldn't allocate weapons");
	node = node->next;
	node->next = NULL;
	node->item = load_shotgun(sounds, map);
	if (!(node->next = (t_weapons *)malloc(sizeof(t_weapons))))
		error_doom("Couldn't allocate weapons");
	node = node->next;
	node->next = NULL;
	node->item = load_vacuum(sounds, map);
	return (first);
}

void		free_weapons(t_weapons *weapons)
{
	t_weapons	*n;
	t_weapons	*p;

	n = weapons;
	while (n)
	{
		free(n->item);
		p = n;
		n = n->next;
		free(p);
	}
}
