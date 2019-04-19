#include <unistd.h>

#include "wall_objects.h"
#include "textures.h"
#include "serialisation.h"
#include "doom.h"

t_wall_object   *create_wall_object(t_textures *textures)
{
	t_wall_object   *object;

	if (!(object = (t_wall_object *)malloc(sizeof(t_wall_object))))
		error_doom("Couldn't allocate new wall object");
	object->offset_on_wall = 0;
	object->z = 0;
	object->size = 1;
	find_texture_by_name(textures, "textures/wall_objects/flag.bmp",
			&object->texture);
	return (object);
}

void			read_wall_object_from_file(
		int fd,
		t_textures *textures,
		t_wall_object **wall_object)
{
	enum e_bool	wall_has_object;

	if (read(fd, &wall_has_object, sizeof(wall_has_object)) <= 0)
		error_doom("can't read wall_has_object");
	*wall_object = NULL;
	if (!wall_has_object)
		return;
	if (!(*wall_object = (t_wall_object*)malloc(sizeof(t_wall_object))))
		error_doom("can't alloc wall_object");
	if (read(fd, &(*wall_object)->offset_on_wall,
			 sizeof((*wall_object)->offset_on_wall)) <= 0)
		error_doom("can't write offset on wall");
	if (read(fd, &(*wall_object)->z, sizeof((*wall_object)->z)) <= 0)
		error_doom("can't write z");
	if (read(fd, &(*wall_object)->size, sizeof((*wall_object)->size)) <= 0)
		error_doom("can't write size");
	find_texture_from_file(fd, textures, &(*wall_object)->texture);
}

void			write_wall_object_to_file(
		int fd,
		t_wall_object *wall_object)
{
	enum e_bool	wall_has_object;

	wall_has_object = wall_object != NULL;
	if (write(fd, &wall_has_object, sizeof(wall_has_object)) <= 0)
		error_doom("can't write wall_has_object");
	if (!wall_has_object)
		return;
	if (write(fd, &wall_object->offset_on_wall,
			  sizeof(wall_object->offset_on_wall)) <= 0)
		error_doom("can't write offset on wall");
	if (write(fd, &wall_object->z, sizeof(wall_object->z)) <= 0)
		error_doom("can't write z");
	if (write(fd, &wall_object->size, sizeof(wall_object->size)) <= 0)
		error_doom("can't write size");
	write_str_to_file(fd, wall_object->texture->userdata);
}
