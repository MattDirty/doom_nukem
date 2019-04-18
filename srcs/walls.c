#include <unistd.h>
#include "walls.h"
#include "textures.h"
#include "doom.h"
#include "serialisation.h"

t_wall      *create_wall_copy(t_wall *wall)
{
    t_wall  *new_wall;

    if (!(new_wall = (t_wall *)malloc(sizeof(t_wall))))
        error_doom("Couldn't allocate copy of wall");
    *new_wall = *wall;
    new_wall->wall_object = NULL;
    new_wall->lever = NULL;
    return (new_wall);
}

void        add_wall_to_sector(t_sector *sector, t_wall *wall)
{
    int     count;
    t_wall  **items;
    int 	i;

    count = sector->walls->count + 1;
    if (!(items = (t_wall **)malloc(sizeof(t_wall *) * count)))
        error_doom("Couldn't add a wall to sector(malloc)");
    i = 0;
    while (i < sector->walls->count)
	{
		*(items + i) = *(sector->walls->items + i);
		i++;
	}
    if (sector->walls->count > 0)
	    free(sector->walls->items);
    *(items + i) = wall;
    sector->walls->items = items;
    sector->walls->count = count;
}

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

static void		fix_levers(
        t_linked_walls *linked_walls)
{
    t_linked_walls	*node;
    t_wall			*door;

    node = linked_walls;
    while (node->wall)
    {
        if (node->wall->lever)
        {
            door = wall_at_index(linked_walls, node->wall->lever->door_index);
            if (door == NULL)
                error_doom("couldn't find door");
            node->wall->lever->door = door;
        }
        node = node->next;
    }
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
    fix_levers(*linked_walls);
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
        while (j < sectors->items[i]->walls->count)
        {
            index = add_wall_to_serialiser(*linked_walls,
                    sectors->items[i]->walls->items[j]);
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
    {
        if (linked_walls->wall->wall_object)
            free(linked_walls->wall->wall_object);
        if (linked_walls->wall->lever)
        {
            if (linked_walls->wall->lever->wall_object)
                free(linked_walls->wall->lever->wall_object);
            free(linked_walls->wall->lever);
        }
        free(linked_walls->wall);
    }
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
        write_wall_to_file(fd, sectors, *p_linked_walls, linked_walls->wall);
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
