#include <unistd.h>

#include "textures.h"
#include "serialisation.h"
#include "sectors.h"
#include "objects.h"
#include "doom.h"

void		free_walls(t_linked_walls *linked_walls)
{
    if (!linked_walls)
        return;
    free_walls(linked_walls->next);
    free(linked_walls);
}

void			read_sectors_from_file(
        int fd,
        t_textures *textures,
        t_sectors **sectors)
{
    int		count;
    int		i;
    t_sector	*sector;
    t_linked_walls*	linked_walls;

    if (!(*sectors = (t_sectors*)malloc(sizeof(t_sectors))))
        error_doom("couldn't malloc t_sectors");
    if (read(fd, &count, sizeof(count)) <= 0)
        error_doom("couldn't read sectors count");
    (*sectors)->count = count;
    (*sectors)->items = (t_sector*)malloc(sizeof(t_sector) * count);
    read_linked_walls_from_file(fd, *sectors, textures, &linked_walls);
    i = 0;
    while (i < count)
    {
        sector = &((*sectors)->items[i]);
        find_texture_from_file(fd, textures, &sector->floor);
        find_texture_from_file(fd, textures, &sector->ceil);
        read_walls_from_file(fd, linked_walls, &sector->walls);
        if (read(fd, &sector->open_sky, sizeof(sector->open_sky)) <= 0)
            error_doom("couldn't read sector open_sky");
        if (read(fd, &sector->light, sizeof(sector->light)) <= 0)
            error_doom("couldn't read sector light");
        read_objects_from_file(fd, textures, &sector->objects);
        read_enemies_from_file(fd, textures, &sector->enemies);
        i++;
    }
    free_walls(linked_walls);
}

void			write_sectors_to_file(int fd, t_sectors *sectors)
{
    int		i;
    t_sector	sector;
    t_linked_walls*	linked_walls;

    if (write(fd, &sectors->count, sizeof(sectors->count)) <= 0)
        error_doom("couldn't write sectors count");
    write_linked_walls_to_file(fd, sectors, &linked_walls);
    i = 0;
    while (i < sectors->count)
    {
        sector = sectors->items[i];
        write_str_to_file(fd, sector.floor->userdata);
        write_str_to_file(fd, sector.ceil->userdata);
        write_walls_to_file(fd, linked_walls, sector.walls);
        if (write(fd, &sector.open_sky, sizeof(sector.open_sky)) <= 0)
            error_doom("couldn't write sector open_sky");
        if (write(fd, &sector.light, sizeof(sector.light)) <= 0)
            error_doom("couldn't write sector light");
        write_objects_to_file(fd, sector.objects);
        write_enemies_to_file(fd, sector.enemies);
        i++;
    }
    free_walls(linked_walls);
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
