#include <unistd.h>
#include "doom.h"
#include "walls.h"
#include "serialisation.h"

void			read_walls_from_file(
		int fd,
		t_linked_walls *linked_walls,
		t_walls **walls)
{
	int		count;
	int		i;
	int		index;

	if (!(*walls = (t_walls*)malloc(sizeof(t_walls))))
		error_doom("couldn't alloc t_walls");

	if (read(fd, &count, sizeof(count)) <= 0)
		error_doom("couldn't read walls count");

	(*walls)->count = count;
	if(!((*walls)->items = (t_wall**)malloc(sizeof(t_wall*) * count)))
		error_doom("error: cannot malloc wall");

	i = 0;
	while (i < count)
	{
		if (read(fd, &index, sizeof(index)) <= 0)
			error_doom("couldn't read wall index");
		*((*walls)->items + i) = wall_at_index(linked_walls, index);
		i++;
	}
}

void			write_walls_to_file(
		int fd,
		t_linked_walls *linked_walls,
		t_walls *walls)
{
	int		i;
	int		index;

	if (write(fd, &walls->count, sizeof(walls->count)) <= 0)
		error_doom("couldn't write walls count");

	i = 0;
	while (i < walls->count)
	{
		index = wall_index(linked_walls, walls->items[i]);
		if (write(fd, &index, sizeof(index)) <= 0)
			error_doom("couldn't write wall index");
		i++;
	}
}

void			read_wall_from_file(
		int fd,
		t_sectors *sectors,
		t_textures *textures,
		t_wall **wall)
{
	int		index;

	if (!(*wall = (t_wall*)malloc(sizeof(t_wall))))
		error_doom("couldn't malloc t_wall");
	(*wall)->wall_offset = 0;
	read_segment_from_file(fd, &(*wall)->segment);
	if (read(fd, &(*wall)->type, sizeof((*wall)->type)) <= 0)
		error_doom("couldn't read wall type");
	(*wall)->texture = NULL;
	if ((*wall)->type == e_wall || (*wall)->type == e_transparent_wall)
		find_texture_from_file(fd, textures, &((*wall)->texture));
	(*wall)->links.sector1 = NULL;
	(*wall)->links.sector2 = NULL;
	if ((*wall)->type == e_portal || (*wall)->type == e_transparent_wall)
	{
		if (read(fd, &index, sizeof(index)) <= 0)
			error_doom("couldn't read first sector index");
		(*wall)->links.sector1 = sectors->items[index];
		if (read(fd, &index, sizeof(index)) <= 0)
			error_doom("couldn't read second sector index");
		(*wall)->links.sector2 = sectors->items[index];
	}
	if (read(fd, &(*wall)->to_infinity, sizeof((*wall)->to_infinity)) <= 0)
		error_doom("Couldn't read wall->to_infinity");
	read_wall_object_from_file(fd, textures, &(*wall)->wall_object);
	read_lever_from_file(fd, textures, &(*wall)->lever);
}

void			write_wall_to_file(
		int fd,
		t_sectors *sectors,
		t_linked_walls *linked_walls,
		t_wall *wall)
{
	int		index;

	write_segment_to_file(fd, &wall->segment);
	if (write(fd, &wall->type, sizeof(wall->type)) <= 0)
		error_doom("couldn't write wall type");
	if (wall->type == e_wall || wall->type == e_transparent_wall)
		write_str_to_file(fd, wall->texture->userdata);
	if (wall->type == e_portal || wall->type == e_transparent_wall)
	{
		index = sector_index(sectors, wall->links.sector1);
		if (index < 0)
			error_doom("index is stupid");
		if (write(fd, &index, sizeof(index)) <= 0)
			error_doom("couldn't write first sector index");
		index = sector_index(sectors, wall->links.sector2);
		if (index < 0)
			error_doom("index is stupid");
		if (write(fd, &index, sizeof(index)) <= 0)
			error_doom("couldn't write second sector index");
	}
	if (write(fd, &wall->to_infinity, sizeof(wall->to_infinity)) <= 0)
		error_doom("Couldn't write wall->to_infinity");
	write_wall_object_to_file(fd, wall->wall_object);
	write_lever_to_file(fd, linked_walls, wall->lever);
}
