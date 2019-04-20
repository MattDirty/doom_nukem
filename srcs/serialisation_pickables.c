/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serialisation_pickables.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfatton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 05:17:03 by lfatton           #+#    #+#             */
/*   Updated: 2019/04/19 05:17:13 by lfatton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "serialisation.h"

void	write_pickable_to_file(int fd, t_pickable pickable)
{
	write_object_to_file(fd, *pickable.object);
	if (write(fd, &pickable.type, sizeof(pickable.type)) <= 0)
		error_doom("Problem while type pickable from file");
	write_str_to_file(fd, pickable.sprite_to_pick[0]->userdata);
	write_str_to_file(fd, pickable.sprite_to_pick[1]->userdata);
	write_str_to_file(fd, pickable.sprite_to_pick[2]->userdata);
}

void	read_pickable_from_file(int fd, t_textures *textures,
			t_pickable *pickable)
{
	if (!(pickable->object = (t_object *)malloc(sizeof(t_object))))
		error_doom("Couldn't allocate object in pickable");
	read_object_from_file(fd, textures, pickable->object);
	if (read(fd, &pickable->type, sizeof(pickable->type)) <= 0)
		error_doom("Problem while reading pickable from file");
	find_texture_from_file(fd, textures, &pickable->sprite_to_pick[0]);
	find_texture_from_file(fd, textures, &pickable->sprite_to_pick[1]);
	find_texture_from_file(fd, textures, &pickable->sprite_to_pick[2]);
}

void	write_pickables_to_file(int fd, t_pickables *pickables)
{
	enum e_bool next;

	next = pickables != NULL;
	if (write(fd, &next, sizeof(next)) <= 0)
		error_doom("mabite");
	if (!next)
		return ;
	write_pickable_to_file(fd, pickables->item);
	write_pickables_to_file(fd, pickables->next);
}

void	read_pickables_from_file(int fd, t_textures *textures,
			t_pickables **pickables)
{
	enum e_bool next;

	if (read(fd, &next, sizeof(next)) <= 0)
		error_doom("The shield has gone mad, Detroudbalus!");
	if (!next)
	{
		*pickables = NULL;
		return ;
	}
	if (!(*pickables = (t_pickables *)malloc(sizeof(t_pickables))))
		error_doom("Couldn't allocate pickables struct");
	(*pickables)->next = NULL;
	read_pickable_from_file(fd, textures, &(*pickables)->item);
	read_pickables_from_file(fd, textures, &(*pickables)->next);
}
