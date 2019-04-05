#include <unistd.h>

#include "walls.h"
#include "textures.h"
#include "serialisation.h"

int			wall_index(t_linked_walls *linked_walls, t_wall *wall)
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

int			add_wall_to_serialiser(
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
    linked_walls->next =
            (t_linked_walls*)malloc(sizeof(t_linked_walls));
    linked_walls->next->next = NULL;
    linked_walls->next->wall = NULL;
    return (i);
}

int			read_linked_walls_from_file(
        int fd,
        t_sectors *sectors,
        t_textures *textures,
        t_linked_walls **linked_walls)
{
    int		i;
    int		count;
    t_wall	*wall;

    if (!(*linked_walls =
            (t_linked_walls*)malloc(sizeof(t_linked_walls))))
        return (-1);
    (*linked_walls)->next = NULL;
    (*linked_walls)->wall = NULL;
    if (read(fd, &count, sizeof(count)) <= 0)
        return (-2);
    i = 0;
    while (i < count)
    {
        if (read_wall_from_file(fd, sectors, textures, &wall) < 0)
            return (-3);
        add_wall_to_serialiser(*linked_walls, wall);
        i++;
    }

    return (0);
}

int			write_linked_walls_to_file(
        int fd,
        t_sectors *sectors,
        t_linked_walls **p_linked_walls)
{
    int		i;
    int		j;
    int		index;
    int		count;
    t_linked_walls *linked_walls;

    if (!(linked_walls =
            (t_linked_walls*)malloc(sizeof(t_linked_walls))))
        return (-1);
    linked_walls->next = NULL;
    linked_walls->wall = NULL;
    *p_linked_walls = linked_walls;
    count = 0;
    i = 0;
    while (i < sectors->count)
    {
        j = 0;
        while (j < sectors->items[i].walls->count)
        {
            index = add_wall_to_serialiser(
                    linked_walls,
                    sectors->items[i].walls->items[j]);
            if (index >= count)
                count = index + 1;
            j++;
        }
        i++;
    }
    if (write(fd, &count, sizeof(count)) <= 0)
        return (-2);
    while (linked_walls->wall)
    {
        if (write_wall_to_file(fd, sectors, linked_walls->wall) < 0)
            return (-3);
        linked_walls = linked_walls->next;
    }
    return (0);
}

int			read_walls_from_file(
        int fd,
        t_linked_walls *linked_walls,
        t_walls **walls)
{
    int		count;
    int		i;
    int		index;

    if (!(*walls = (t_walls*)malloc(sizeof(t_walls))))
        return (-1);

    if (read(fd, &count, sizeof(count)) <= 0)
        return (-2);

    (*walls)->count = count;
    (*walls)->items = (t_wall**)malloc(sizeof(t_wall*) * count);

    i = 0;
    while (i < count)
    {
        if (read(fd, &index, sizeof(index)) <= 0)
            return (-3);
        *((*walls)->items + i) = wall_at_index(linked_walls, index);

        i++;
    }

    return (0);
}

int			write_walls_to_file(
        int fd,
        t_linked_walls *linked_walls,
        t_walls *walls)
{
    int		i;
    int		index;

    if (write(fd, &walls->count, sizeof(walls->count)) <= 0)
        return (-1);

    i = 0;
    while (i < walls->count)
    {
        index = wall_index(linked_walls, walls->items[i]);
        if (write(fd, &index, sizeof(index)) <= 0)
            return (-2);

        i++;
    }

    return (0);
}

int			read_wall_from_file(
        int fd,
        t_sectors *sectors,
        t_textures *textures,
        t_wall **wall)
{
    int		index;

    if (!(*wall = (t_wall*)malloc(sizeof(t_wall))))
        return (-1);
    if (read(fd, &(*wall)->height, sizeof((*wall)->height)) <= 0)
        return (-1);
    if (!read_segment_from_file(fd, &(*wall)->segment))
        return (-2);
    if (read(fd, &(*wall)->type, sizeof((*wall)->type)) <= 0)
        return (-3);
    if ((*wall)->type == e_wall)
    {
        if (find_texture_from_file(fd, textures, &((*wall)->pointer.texture)) < 0)
            return (-5);
    }
    else if ((*wall)->type == e_portal)
    {
        if (read(fd, &index, sizeof(index)) <= 0)
            return (-5);
        (*wall)->pointer.sector.sector1 = (t_sector*)sectors->items + index;
        if (read(fd, &index, sizeof(index)) <= 0)
            return (-6);
        (*wall)->pointer.sector.sector2 = (t_sector*)sectors->items + index;
    }
    return (0);
}

int			write_wall_to_file(
        int fd,
        t_sectors *sectors,
        t_wall *wall)
{
    int		index;

    if (write(fd, &wall->height, sizeof(wall->height)) <= 0)
        return (-1);
    if (write_segment_to_file(fd, &wall->segment) <= 0)
        return (-2);
    if (write(fd, &wall->type, sizeof(wall->type)) <= 0)
        return (-3);
    if (wall->type == e_wall)
    {
        if (write_str_to_file(fd, wall->pointer.texture->userdata) < 0)
            return (-4);
    }
    else if (wall->type == e_portal)
    {
        index = sector_index(sectors, wall->pointer.sector.sector1);
        if (index < 0)
            return (-5);
        if (write(fd, &index, sizeof(index)) <= 0)
            return (-6);
        index = sector_index(sectors, wall->pointer.sector.sector2);
        if (index < 0)
            return (-7);
        if (write(fd, &index, sizeof(index)) <= 0)
            return (-8);
    }
    return (0);
}
