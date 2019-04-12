#include <unistd.h>

#include "walls.h"
#include "textures.h"
#include "doom.h"
#include "serialisation.h"

static int			wall_index(t_linked_walls *linked_walls, t_wall *wall)
{
    int		i;

    i = 0;
    while (linked_walls)
    {
        if (wall == linked_walls->wall)
            return (i);
        linked_walls = linked_walls->next;
        i++;
    }
    return (-1);
}

t_wall		*wall_at_index(t_linked_walls *linked_walls, int index)
{
    int		i;

    i = 0;
    while (linked_walls->next)
    {
        if (index == i)
            return (linked_walls->wall);
        linked_walls = linked_walls->next;
        i++;
    }
    return (NULL);
}

static int			add_wall_to_serialiser(
        t_linked_walls *linked_walls,
        t_wall *wall)
{
    int		i;

    i = 0;
    while (linked_walls->wall)
    {
        if (linked_walls->wall == wall)
            return (i);
        linked_walls = linked_walls->next;
        i++;
    }
    linked_walls->wall = wall;
    if (!(linked_walls->next = (t_linked_walls*)malloc(sizeof(t_linked_walls))))
        error_doom("couldn't malloc t_linked_walls");
    linked_walls->next->next = NULL;
    linked_walls->next->wall = NULL;
    return (i);
}

void			read_linked_walls_from_file(
        int fd,
        t_sectors *sectors,
        t_textures *textures,
        t_linked_walls **linked_walls)
{
    int		i;
    int		count;
    t_wall	*wall;

    if (!(*linked_walls = (t_linked_walls*)malloc(sizeof(t_linked_walls))))
        error_doom("couldn't malloc t_linked_walls");
    (*linked_walls)->next = NULL;
    (*linked_walls)->wall = NULL;
    if (read(fd, &count, sizeof(count)) <= 0)
        error_doom("couldn't read linked_walls");
    i = 0;
    while (i < count)
    {
        read_wall_from_file(fd, sectors, textures, &wall);
        add_wall_to_serialiser(*linked_walls, wall);
        i++;
    }
}

void			create_linked_walls_from_sectors(
        t_sectors *sectors,
        t_linked_walls **linked_walls,
        int *count)
{
    int		i;
    int		j;
    int		index;

    if (!(*linked_walls = (t_linked_walls*)malloc(sizeof(t_linked_walls))))
        error_doom("couldn't malloc linked walls");
    (*linked_walls)->next = NULL;
    (*linked_walls)->wall = NULL;
    *count = 0;
    i = 0;
    while (i < sectors->count)
    {
        j = 0;
        while (j < sectors->items[i].walls->count)
        {
            index = add_wall_to_serialiser(*linked_walls,
                    sectors->items[i].walls->items[j]);
            if (index >= *count)
                *count = index + 1;
            j++;
        }
        i++;
    }
}

void		free_linked_walls_nodes(t_linked_walls *linked_walls)
{
    if (!linked_walls)
        return;
    free_linked_walls_nodes(linked_walls->next);
    free(linked_walls);
}

void		free_linked_walls(t_linked_walls *linked_walls)
{
    if (!linked_walls)
        return;
    free_linked_walls(linked_walls->next);
    if (linked_walls->wall)
        free(linked_walls->wall);
    free(linked_walls);
}

void			write_linked_walls_to_file(
        int fd,
        t_sectors *sectors,
        t_linked_walls **p_linked_walls)
{
    t_linked_walls *linked_walls;
    int		count;

    create_linked_walls_from_sectors(sectors, p_linked_walls, &count);
    linked_walls = *p_linked_walls;
    if (write(fd, &count, sizeof(count)) <= 0)
        error_doom("couldn't write walls count");
    while (linked_walls->wall)
    {
        write_wall_to_file(fd, sectors, linked_walls->wall);
        linked_walls = linked_walls->next;
    }
}

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
    (*walls)->items = (t_wall**)malloc(sizeof(t_wall*) * count);

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
    read_segment_from_file(fd, &(*wall)->segment);
    if (read(fd, &(*wall)->type, sizeof((*wall)->type)) <= 0)
        error_doom("couldn't read wall type");
    if ((*wall)->type == e_wall || (*wall)->type == e_transparent_wall)
        find_texture_from_file(fd, textures, &((*wall)->texture));
    else if ((*wall)->type == e_portal)
        (*wall)->texture = NULL;
    if ((*wall)->type == e_portal || (*wall)->type == e_transparent_wall)
    {
        if (read(fd, &index, sizeof(index)) <= 0)
            error_doom("couldn't read first sector index");
        (*wall)->links.sector1 = (t_sector*)sectors->items + index;
        if (read(fd, &index, sizeof(index)) <= 0)
            error_doom("couldn't read second sector index");
        (*wall)->links.sector2 = (t_sector*)sectors->items + index;
    }
    else if ((*wall)->type == e_wall)
    {
        (*wall)->links.sector1 = NULL;
        (*wall)->links.sector2 = NULL;
    }
    if (read(fd, &(*wall)->to_infinity, sizeof((*wall)->to_infinity)) <= 0)
        error_doom("Couldn't read wall->to_infinity");
    read_wall_object_from_file(fd, textures, &(*wall)->wall_object);
}

void			write_wall_to_file(
        int fd,
        t_sectors *sectors,
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
