#include <unistd.h>

#include "textures.h"
#include "serialisation.h"
#include "sectors.h"

void		free_walls(t_linked_walls *linked_walls)
{
    if (!linked_walls)
        return;
    free_walls(linked_walls->next);
    free(linked_walls);
}

int			read_sectors_from_file(
        int fd,
        t_textures *textures,
        t_sectors **sectors)
{
    int		count;
    int		i;
    t_sector	*sector;
    t_linked_walls*	linked_walls;

    if (!(*sectors = (t_sectors*)malloc(sizeof(t_sectors))))
        return (-1);
    if (read(fd, &count, sizeof(count)) <= 0)
        return (-2);
    (*sectors)->count = count;
    (*sectors)->items = (t_sector*)malloc(sizeof(t_sector) * count);
    if (read_linked_walls_from_file(
            fd,
            *sectors,
            textures,
            &linked_walls) < 0)
        return (-3);
    i = 0;
    while (i < count)
    {
        sector = &((*sectors)->items[i]);
        if (find_texture_from_file(fd, textures, &sector->floor) < 0)
            return (-4);
        if (find_texture_from_file(fd, textures, &sector->ceil) < 0)
            return (-5);
        if (read_walls_from_file(fd, linked_walls, &sector->walls) < 0)
            return (-6);
        if (read(fd, &sector->open_sky, sizeof(sector->open_sky)) <= 0)
            return (-7);
        if (read(fd, &sector->light, sizeof(sector->light)) <= 0)
        	return (-8);
        i++;
    }
    free_walls(linked_walls);
    return (0);
}

int			write_sectors_to_file(int fd, t_sectors *sectors)
{
    int		i;
    t_sector	sector;
    t_linked_walls*	linked_walls;

    if (write(fd, &sectors->count, sizeof(sectors->count)) <= 0)
        return (-1);
    if (write_linked_walls_to_file(
            fd,
            sectors,
            &linked_walls) < 0)
        return (-2);
    i = 0;
    while (i < sectors->count)
    {
        sector = sectors->items[i];
        if (write_str_to_file(fd, sector.floor->userdata) < 0)
            return (-3);
        if (write_str_to_file(fd, sector.ceil->userdata) < 0)
            return (-4);
        if (write_walls_to_file(fd, linked_walls, sector.walls) < 0)
            return (-5);
        if (write(fd, &sector.open_sky, sizeof(sector.open_sky)) <= 0)
            return (-7);
        if (write(fd, &sector.light, sizeof(sector.light)) <= 0)
        	return (-8);
        i++;
    }
    free_walls(linked_walls);
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
