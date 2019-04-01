#include <unistd.h>

#include "walls.h"
#include "textures.h"
#include "serialisation.h"

int			read_walls_from_file(
        int fd,
        t_sectors *sectors,
        t_textures *textures,
        t_walls **walls)
{
    int		count;
    int		i;

    if (!(*walls = (t_walls*)malloc(sizeof(t_walls))))
        return (-1);

    if (read(fd, &count, sizeof(count)) <= 0)
        return (-2);

    (*walls)->count = count;
    (*walls)->items = (t_wall**)malloc(sizeof(t_wall*) * count);

    i = 0;
    while (i < count)
    {
        if (read_wall_from_file(fd, sectors, textures, (*walls)->items + i) < 0)
            return (-3);

        i++;
    }

    return (0);
}

int			write_walls_to_file(int fd, t_sectors *sectors, t_walls *walls)
{
    int		i;

    if (write(fd, &walls->count, sizeof(walls->count)) <= 0)
        return (-1);

    i = 0;
    while (i < walls->count)
    {
        if (write_wall_to_file(fd, sectors, walls->items[i]) < 0)
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
        find_texture_by_name(textures, name, &((*wall)->pointer.texture));
        free(name);
    }
    else if ((*wall)->type == wtPortal)
    {
        if (read(fd, &index, sizeof(index)) <= 0)
            return (-5);
        (*wall)->pointer.sector.sector1 = (t_sector*)(sectors + index);
        if (read(fd, &index, sizeof(index)) <= 0)
            return (-6);
        (*wall)->pointer.sector.sector2 = (t_sector*)(sectors + index);
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
