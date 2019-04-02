#include <unistd.h>

#include "serialisation.h"
#include "sectors.h"

int			read_sectors_from_file(
        int fd,
        t_textures *textures,
        t_sectors **sectors)
{
    int		count;
    int		i;
    t_sector	*sector;
    t_walls_serialiser*	walls_serialiser;
    char	*name;

    if (!(*sectors = (t_sectors*)malloc(sizeof(t_sectors))))
        return (-1);

    if (read(fd, &count, sizeof(count)) <= 0)
        return (-2);

    (*sectors)->count = count;
    (*sectors)->items = (t_sector*)malloc(sizeof(t_sector) * count);

    if (read_walls_serialiser_from_file(
            fd,
            *sectors,
            textures,
            &walls_serialiser) < 0)
        return (-3);

    i = 0;
    while (i < count)
    {
        sector = &((*sectors)->items[i]);
        if (read_str_from_file(fd, &name) < 0)
            return (-3);
        if (find_texture_by_name(textures, name, &sector->floor) < 0)
            return (-4);
        if (read_str_from_file(fd, &name) < 0)
            return (-5);
        if (find_texture_by_name(textures, name, &sector->ceil) < 0)
            return (-6);
        if (read_walls_from_file(fd, walls_serialiser, &sector->walls) < 0)
            return (-7);

        i++;
    }
    free(walls_serialiser);

    return (0);
}

int			write_sectors_to_file(int fd, t_sectors *sectors)
{
    int		i;
    t_sector	sector;
    t_walls_serialiser*	walls_serialiser;

    if (write(fd, &sectors->count, sizeof(sectors->count)) <= 0)
        return (-1);

    if (write_walls_serialiser_to_file(
            fd,
            sectors,
            &walls_serialiser) < 0)
        return (-2);

    i = 0;
    while (i < sectors->count)
    {
        sector = sectors->items[i];
        if (write_str_to_file(fd, sector.floor->userdata) < 0)
            return (-3);
        if (write_str_to_file(fd, sector.ceil->userdata) < 0)
            return (-4);
        if (write_walls_to_file(fd, walls_serialiser, sector.walls) < 0)
            return (-5);

        i++;
    }
    free(walls_serialiser);

    return (0);
}

int     sector_index(t_sectors *sectors, t_sector *sector)
{
    int		i;

    i = 0;
    while(i < sectors->count)
    {
        if (sector == sectors->items + i)
            return (i);
        i++;
    }
    return (-1);
}
