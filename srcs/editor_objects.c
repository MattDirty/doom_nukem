/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_objects.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfatton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 05:07:16 by lfatton           #+#    #+#             */
/*   Updated: 2019/04/19 05:07:17 by lfatton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"
#include "doom.h"

void        remove_object(t_object *object, t_objects *objects)
{
	int     i;
	int     j;
	int     k;
	t_object    *items;

	i = 0;
	while (object != objects->items + i)
		i++;
	if (!(items = (t_object *)malloc(sizeof(t_object) * objects->count - 1)))
		error_doom("Couldn't alloc new objects list");
	j = 0;
	k = -1;
	while (++k < objects->count - 1)
	{
		if (j == i)
		{
			j++;
			continue;
		}
		items[k] = objects->items[j];
		j++;
	}
	free(objects->items);
	objects->items = items;
	objects->count--;
}

t_object    create_default_object(t_textures *textures)
{
	t_object    new_object;

	new_object.x = 0;
	new_object.y = 0;
	new_object.z = 0;
	new_object.horizontal_size = 1;
	new_object.vertical_size = 1;
	find_texture_by_name(textures, "textures/sprites/voilaunefleur.bmp",
						 &new_object.sprite);
	new_object.can_give_bonus = e_true;
	return (new_object);
}

t_object    *add_new_object_to_sector_at_pos(
		t_sector *sector, t_coords pos, t_textures *textures)
{
	t_object    object;
	t_object    *items;
	int         i;
	int         count;

	if (sector->objects->count >= 12)
		return (NULL);
	object = create_default_object(textures);
	object.x = pos.x;
	object.y = pos.y;
	count = sector->objects->count + 1;
	if (!(items = (t_object *)malloc(sizeof(t_object) * count)))
		error_doom("couldn't reallocate objects");
	i = 0;
	while (i < count - 1)
	{
		items[i] = sector->objects->items[i];
		i++;
	}
	items[i] = object;
	if (sector->objects->count)
		free(sector->objects->items);
	sector->objects->items = items;
	sector->objects->count = count;
	return (&items[i]);
}
