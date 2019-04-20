/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_pickables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfatton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 05:07:27 by lfatton           #+#    #+#             */
/*   Updated: 2019/04/19 05:07:28 by lfatton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pickables.h"
#include "doom.h"

int			count_pickables(t_pickables *pickables)
{
	int	i;

	i = 0;
	while (pickables)
	{
		pickables = pickables->next;
		i++;
	}
	return (i);
}

t_pickable	create_default_pickable(t_textures *textures)
{
	t_pickable	new_pickable;

	if (!(new_pickable.object = (t_object *)malloc(sizeof(t_object))))
		error_doom("Couldn't allocate object in pickable");
	*new_pickable.object = create_default_object(textures);
	new_pickable.type = et_gun;
	find_texture_by_name(textures, "textures/sprites/gun.bmp",
			&new_pickable.sprite_to_pick[0]);
	find_texture_by_name(textures, "textures/sprites/shotgun.bmp",
			&new_pickable.sprite_to_pick[1]);
	find_texture_by_name(textures, "textures/sprites/vacuum.bmp",
			&new_pickable.sprite_to_pick[2]);
	return (new_pickable);
}

void		add_pickable(t_pickables **pickables, t_pickables *pickable)
{
	t_pickables	*node;

	if (!*pickables)
	{
		*pickables = pickable;
		return ;
	}
	node = *pickables;
	while (node->next)
		node = node->next;
	node->next = pickable;
}

t_pickables	*add_new_pickable_to_sector_at_pos(t_sector *sector, t_coords pos,
				t_textures *textures)
{
	t_pickables	*new_pickables;

	if (count_pickables(sector->pickables) > 6)
		return (NULL);
	if (!(new_pickables = (t_pickables *)malloc(sizeof(t_pickables))))
		error_doom("couldn't allocate new pickable");
	new_pickables->next = NULL;
	new_pickables->item = create_default_pickable(textures);
	new_pickables->item.object->x = pos.x;
	new_pickables->item.object->y = pos.y;
	new_pickables->item.object->sprite = new_pickables->item.sprite_to_pick[0];
	add_pickable(&sector->pickables, new_pickables);
	return (new_pickables);
}
