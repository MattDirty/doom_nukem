#include <unistd.h>

#include "walls.h"
#include "textures.h"
#include "serialisation.h"

int			read_walls_from_file(int fd, t_textures *textures, t_walls **walls)
{
    int		count;
    int		i;
    t_wall	*wall;
    char	*name;

    if (!(*walls = (t_walls*)malloc(sizeof(t_walls))))
        return (-1);

    if (read(fd, &count, sizeof(count)) <= 0)
        return (-2);

    (*walls)->count = count;
    (*walls)->items = (t_wall*)malloc(sizeof(t_wall) * count);

    i = 0;
    while (i < count)
    {
        wall = &((*walls)->items[i]);
        if (!(wall = (t_wall*)malloc(sizeof(t_wall))))
            return (-3);
        if (read(fd, &(wall->height), sizeof(wall->height)) <= 0)
            return (-3);
        if (read(fd, &(wall->portal), sizeof(wall->portal)) <= 0)
            return (-4);
        if (!read_segment_from_file(fd, &wall->segment))
            return (-5);
        if (!read_str_from_file(fd, &name))
            return (-6);
        find_texture_by_name(textures, name, &(wall->texture));
        free(name);

        i++;
    }

    return (0);
}

int			write_walls_to_file(int fd, t_walls *walls)
{
    int		i;
    t_wall	wall;

    if (write(fd, &walls->count, sizeof(walls->count)) <= 0)
        return (-1);

    i = 0;
    while (i < walls->count)
    {
        wall = walls->items[i];

        write(fd, &wall.height, sizeof(wall.height));
        write(fd, &wall.portal, sizeof(wall.portal));
        write_segment_to_file(fd, &wall.segment);
        write_str_to_file(fd, wall.texture->userdata);

        i++;
    }

    return (0);
}
