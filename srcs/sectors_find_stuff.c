/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sectors_find_stuff.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtorsell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/20 03:56:42 by mtorsell          #+#    #+#             */
/*   Updated: 2019/04/20 03:56:43 by mtorsell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "textures.h"
#include "serialisation.h"
#include "sectors.h"
#include "objects.h"
#include "doom.h"
#include "enemies.h"
#include "utils.h"

t_sector	*find_pickable_sector(t_sectors *sectors, t_pickable *pickable)
{
	int			i;
	t_pickables	*node;

	i = 0;
	while (i < sectors->count)
	{
		node = sectors->items[i]->pickables;
		while (node)
		{
			if (pickable == &node->item)
				return (sectors->items[i]);
			node = node->next;
		}
		i++;
	}
	return (NULL);
}

t_sector	*find_enemy_sector(t_sectors *sectors, t_enemy *enemy)
{
	int					i;
	t_linked_enemies	*node;

	i = 0;
	while (i < sectors->count)
	{
		node = sectors->items[i]->enemies;
		while (node)
		{
			if (enemy == &node->item)
				return (sectors->items[i]);
			node = node->next;
		}
		i++;
	}
	return (NULL);
}

t_sector	*find_object_sector(t_sectors *sectors, t_object *object)
{
	int i;
	int j;

	i = 0;
	while (i < sectors->count)
	{
		j = 0;
		while (j < sectors->items[i]->objects->count)
		{
			if (sectors->items[i]->objects->items + j == object)
				return (sectors->items[i]);
			j++;
		}
		i++;
	}
	return (NULL);
}

t_sector	*find_wall_sector(t_sectors *sectors, t_wall *wall)
{
	int i;
	int j;

	i = 0;
	while (i < sectors->count)
	{
		j = 0;
		while (j < sectors->items[i]->walls->count)
		{
			if (sectors->items[i]->walls->items[j] == wall)
				return (sectors->items[i]);
			j++;
		}
		i++;
	}
	return (NULL);
}
