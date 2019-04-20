/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pickables.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badhont <badhont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 04:22:46 by badhont           #+#    #+#             */
/*   Updated: 2019/04/19 04:35:00 by badhont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pickables.h"
#include "doom.h"
#include "e_bool.h"
#include "utils.h"
#include "sectors.h"

t_pickables	*extract_pickable(t_pickables **pickables, t_pickable *pickable)
{
	t_pickables	*previous;
	t_pickables	*node;

	if (pickable == &(*pickables)->item)
	{
		previous = *pickables;
		*pickables = previous->next;
		previous->next = NULL;
		return (previous);
	}
	previous = NULL;
	node = *pickables;
	while (node)
	{
		if (&node->item == pickable)
		{
			previous->next = node->next;
			node->next = NULL;
			return (node);
		}
		previous = node;
		node = node->next;
	}
	return (NULL);
}

void		delete_pickable(t_pickables **pickables, t_pickable *to_delete)
{
	t_pickables *node;

	node = extract_pickable(pickables, to_delete);
	if (!node)
		return ;
	free(node->item.object);
	free(node);
}

void		do_stuff(t_player *player, t_pickables *pickables)
{
	if (pickables->item.type == et_gun)
		make_weapon_usable(player->weapons, 1);
	else if (pickables->item.type == et_shotgun)
		make_weapon_usable(player->weapons, 2);
	else if (pickables->item.type == et_vacuum)
		make_weapon_usable(player->weapons, 3);
	else
		error_doom("invalid pickable");
}

void		pick_objects(t_player *player)
{
	t_pickables	*pickables;
	t_pickables	*next;
	t_coords	pick_pos;

	pickables = player->current_sector->pickables;
	while (pickables)
	{
		pick_pos = (t_coords){pickables->item.object->x,
						pickables->item.object->y};
		if (is_close_to(pick_pos, player->pos, 0.5))
		{
			do_stuff(player, pickables);
			next = pickables->next;
			delete_pickable(&player->current_sector->pickables,
					&pickables->item);
			pickables = next;
			continue ;
		}
		pickables = pickables->next;
	}
}

void		free_pickables(t_pickables *pickables)
{
	if (!pickables)
		return ;
	free_pickables(pickables->next);
	free(pickables->item.object);
	free(pickables);
}
