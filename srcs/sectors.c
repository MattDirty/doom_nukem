#include <unistd.h>

#include "sectors.h"

int			read_sectors_from_file(
        int fd,
        t_textures *textures,
        t_sectors **sectors)
{
    int		count;
    int		i;
    t_sector	*sector;

    if (!(*sectors = (t_sectors*)malloc(sizeof(t_sectors))))
        return (-1);

    if (read(fd, &count, sizeof(count)) <= 0)
        return (-2);

    (*sectors)->count = count;
    (*sectors)->items = (t_sector*)malloc(sizeof(t_sector) * count);

    i = 0;
    while (i < count)
    {
        sector = &((*sectors)->items[i]);
        if (read_walls_from_file(fd, *sectors, textures, &sector->walls) < 0)
            return (-3);

        i++;
    }

    return (0);
}

int			write_sectors_to_file(int fd, t_sectors *sectors)
{
    int		i;
    t_sector	sector;

    if (write(fd, &sectors->count, sizeof(sectors->count)) <= 0)
        return (-1);

    i = 0;
    while (i < sectors->count)
    {
        sector = sectors->items[i];
        if (write_walls_to_file(fd, sectors, sector.walls) < 0)
            return (-2);

        i++;
    }

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
