#include <unistd.h>

#include "walls.h"
#include "textures.h"
#include "serialisation.h"

int			wall_index(t_walls_serialiser *walls_serialiser, t_wall *wall)
{
    int		i;

    i = 0;
    while (walls_serialiser)
    {
        if (wall == walls_serialiser->wall)
            return (i);
        walls_serialiser = walls_serialiser->next;
        i++;
    }
    return (-1);
}

t_wall		*wall_at_index(t_walls_serialiser *walls_serialiser, int index)
{
    int		i;

    i = 0;
    while (walls_serialiser->next)
    {
        if (index == i)
            return (walls_serialiser->wall);
        walls_serialiser = walls_serialiser->next;
        i++;
    }
    return (NULL);
}

int			add_wall_to_serialiser(
        t_walls_serialiser *walls_serialiser,
        t_wall *wall)
{
    int		i;

    i = 0;
    while (walls_serialiser->wall)
    {
        if (walls_serialiser->wall == wall)
            return (i);
        walls_serialiser = walls_serialiser->next;
        i++;
    }
    walls_serialiser->wall = wall;
    walls_serialiser->next =
            (t_walls_serialiser*)malloc(sizeof(t_walls_serialiser));
    walls_serialiser->next->next = NULL;
    walls_serialiser->next->wall = NULL;
    return (i);
}

int			read_walls_serialiser_from_file(
        int fd,
        t_sectors *sectors,
        t_textures *textures,
        t_walls_serialiser **walls_serialiser)
{
    int		i;
    int		count;
    t_wall	*wall;

    if (!(*walls_serialiser =
            (t_walls_serialiser*)malloc(sizeof(t_walls_serialiser))))
        return (-1);
    (*walls_serialiser)->next = NULL;
    (*walls_serialiser)->wall = NULL;
    if (read(fd, &count, sizeof(count)) <= 0)
        return (-2);
    i = 0;
    while (i < count)
    {
        if (read_wall_from_file(fd, sectors, textures, &wall) < 0)
            return (-3);
        add_wall_to_serialiser(*walls_serialiser, wall);
        i++;
    }

    return (0);
}

int			write_walls_serialiser_to_file(
        int fd,
        t_sectors *sectors,
        t_walls_serialiser **p_walls_serialiser)
{
    int		i;
    int		j;
    int		index;
    int		count;
    t_walls_serialiser *walls_serialiser;

    if (!(walls_serialiser =
            (t_walls_serialiser*)malloc(sizeof(t_walls_serialiser))))
        return (-1);
    walls_serialiser->next = NULL;
    walls_serialiser->wall = NULL;
    *p_walls_serialiser = walls_serialiser;
    count = 0;
    i = 0;
    while (i < sectors->count)
    {
        j = 0;
        while (j < sectors->items[i].walls->count)
        {
            index = add_wall_to_serialiser(
                    walls_serialiser,
                    sectors->items[i].walls->items[j]);
            if (index >= count)
                count = index + 1;
            j++;
        }
        i++;
    }
    if (write(fd, &count, sizeof(count)) <= 0)
        return (-2);
    while (walls_serialiser->wall)
    {
        if (write_wall_to_file(fd, sectors, walls_serialiser->wall) < 0)
            return (-3);
        walls_serialiser = walls_serialiser->next;
    }
    return (0);
}

int			read_walls_from_file(
        int fd,
        t_walls_serialiser *walls_serialiser,
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
        *((*walls)->items + i) = wall_at_index(walls_serialiser, index);

        i++;
    }

    return (0);
}

int			write_walls_to_file(
        int fd,
        t_walls_serialiser *walls_serialiser,
        t_walls *walls)
{
    int		i;
    int		index;

    if (write(fd, &walls->count, sizeof(walls->count)) <= 0)
        return (-1);

    i = 0;
    while (i < walls->count)
    {
        index = wall_index(walls_serialiser, walls->items[i]);
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
    char	*name;

    if (!(*wall = (t_wall*)malloc(sizeof(t_wall))))
        return (-1);
    if (read(fd, &(*wall)->height, sizeof((*wall)->height)) <= 0)
        return (-1);
    if (!read_segment_from_file(fd, &(*wall)->segment))
        return (-2);
    if (read(fd, &(*wall)->type, sizeof((*wall)->type)) <= 0)
        return (-3);
    if ((*wall)->type == wtWall)
    {
        if (read_str_from_file(fd, &name) < 0)
            return (-4);
        if (find_texture_by_name(textures, name, &((*wall)->pointer.texture)) < 0)
            return (-5);
        free(name);
    }
    else if ((*wall)->type == wtPortal)
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
    if (wall->type == wtWall)
    {
        if (write_str_to_file(fd, wall->pointer.texture->userdata) < 0)
            return (-4);
    }
    else if (wall->type == wtPortal)
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
