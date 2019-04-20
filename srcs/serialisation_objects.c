/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serialisation_objects.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfatton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 05:09:34 by lfatton           #+#    #+#             */
/*   Updated: 2019/04/19 05:09:35 by lfatton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "serialisation.h"

void	read_objects_from_file(int fd, t_textures *textures,
			t_objects **objects)
{
	int count;
	int i;

	if (!(*objects = (t_objects *)malloc(sizeof(t_objects))))
		error_doom("couldn't malloc t_objects");
	if (read(fd, &count, sizeof(count)) <= 0)
		error_doom("couldn't read objects count");
	(*objects)->count = count;
	if (count > 0)
	{
		if (!((*objects)->items = (t_object *)malloc(
				sizeof(t_object) * count)))
			error_doom("couldn't malloc t_objects->items");
	}
	else
		(*objects)->items = NULL;
	i = 0;
	while (i < (*objects)->count)
	{
		read_object_from_file(fd, textures, &(*objects)->items[i]);
		i++;
	}
}

void	write_objects_to_file(int fd, t_objects *objects)
{
	int i;

	if (write(fd, &objects->count, sizeof(objects->count)) <= 0)
		error_doom("couldn't write objects count");
	i = 0;
	while (i < objects->count)
	{
		write_object_to_file(fd, objects->items[i]);
		i++;
	}
}

void	read_object_from_file(int fd, t_textures *textures, t_object *object)
{
	if (read(fd, &object->can_give_bonus, sizeof(object->can_give_bonus)) <= 0)
		error_doom("couldn't read object bool can_give_bonus");
	if (read(fd, &object->x, sizeof(object->x)) <= 0)
		error_doom("couldn't read object x");
	if (read(fd, &object->y, sizeof(object->y)) <= 0)
		error_doom("couldn't read object y");
	if (read(fd, &object->z, sizeof(object->z)) <= 0)
		error_doom("couldn't read object z");
	if (read(fd, &object->horizontal_size, sizeof(object->horizontal_size)) <=
		0)
		error_doom("couldn't read object horizontal_size");
	if (read(fd, &object->vertical_size, sizeof(object->vertical_size)) <= 0)
		error_doom("couldn't read object vertical_size");
	find_texture_from_file(fd, textures, &object->sprite);
}

void	write_object_to_file(int fd, t_object object)
{
	if (write(fd, &object.can_give_bonus, sizeof(object.can_give_bonus)) <= 0)
		error_doom("couldn't write object bool can_give_bonus");
	if (write(fd, &object.x, sizeof(object.x)) <= 0)
		error_doom("couldn't write object x");
	if (write(fd, &object.y, sizeof(object.y)) <= 0)
		error_doom("couldn't write object y");
	if (write(fd, &object.z, sizeof(object.z)) <= 0)
		error_doom("couldn't write object z");
	if (write(fd, &object.horizontal_size, sizeof(object.horizontal_size)) <= 0)
		error_doom("couldn't write object horizontal_size");
	if (write(fd, &object.vertical_size, sizeof(object.vertical_size)) <= 0)
		error_doom("couldn't write object vertical_size");
	write_str_to_file(fd, object.sprite->userdata);
}
