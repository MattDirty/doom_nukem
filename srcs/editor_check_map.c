/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_check_map.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfatton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/20 07:29:11 by lfatton           #+#    #+#             */
/*   Updated: 2019/04/20 07:29:13 by lfatton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "editor_walls_nodes.h"
#include "in_which_sector.h"
#include "editor_checks.h"

enum e_bool	is_object_in_sector(t_sector *sector, t_object *object)
{
	return (is_in_sector((t_coords){object->x, object->y}, sector));
}

enum e_bool	are_objects_in_sector_valid(t_sector *sector)
{
	int	j;

	j = 0;
	while (j < sector->objects->count)
	{
		if (!is_object_in_sector(sector, &sector->objects->items[j]))
			return (e_false);
		j++;
	}
	return (e_true);
}

enum e_bool	are_enemies_in_sector_valid(t_sector *sector)
{
	t_linked_enemies *e_node;

	e_node = sector->enemies;
	while (e_node)
	{
		if (!is_object_in_sector(sector, e_node->item.object))
			return (e_false);
		e_node = e_node->next;
	}
	return (e_true);
}

enum e_bool	are_pickables_in_sector_valid(t_sector *sector)
{
	t_pickables	*node;

	node = sector->pickables;
	while (node)
	{
		if (!is_object_in_sector(sector, node->item.object))
			return (e_false);
		node = node->next;
	}
	return (e_true);
}

enum e_bool	is_map_valid(t_linked_walls *walls, t_map *map)
{
	int			i;
	t_sector	*sector;

	if (walls_intersect_on_map(walls))
		return (e_false);
	if (!in_which_sector(map->spawn, map->sectors))
		return (e_false);
	i = 0;
	while (i < map->sectors->count)
	{
		sector = map->sectors->items[i];
		if (!are_objects_in_sector_valid(sector)
			|| !are_enemies_in_sector_valid(sector)
			|| !are_pickables_in_sector_valid(sector))
			return (e_false);
		i++;
	}
	return (e_true);
}
