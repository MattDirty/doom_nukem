#include "objects.h"

#include <unistd.h>

#include "textures.h"
#include "serialisation.h"

int read_objects_from_file(int fd, t_textures *textures, t_objects **objects)
{
    int count;
    int i;

    if (!(*objects = (t_objects*)malloc(sizeof(t_objects))))
        return (-1);
    if (read(fd, &count, sizeof(count)) <= 0)
        return (-2);
    (*objects)->count = count;
    if (!((*objects)->items = (t_object*)malloc(sizeof(t_object) * count)))
        return (-3);
    i = 0;
    while (i < (*objects)->count)
    {
        if (read_object_from_file(fd, textures, &(*objects)->items[i]) < 0)
            return (-4);
        i++;
    }
    return (0);
}

int write_objects_to_file(int fd, t_objects *objects)
{
    int i;

    if (write(fd, &objects->count, sizeof(objects->count)) <= 0)
        return (-1);
    i = 0;
    while (i < objects->count)
    {
        if (write_object_to_file(fd, objects->items[i]) < 0)
            return (-2);
        i++;
    }
    return (0);
}

int read_object_from_file(int fd, t_textures *textures, t_object *object)
{
    if (read(fd, &object->x, sizeof(object->x)) <= 0)
        return (-1);
    if (read(fd, &object->y, sizeof(object->y)) <= 0)
        return (-2);
    if (find_texture_from_file(fd, textures, &object->sprite) < 0)
        return (-3);
    return (0);
}

int write_object_to_file(int fd, t_object object)
{
    if (write(fd, &object.x, sizeof(object.x)) <= 0)
        return (-1);
    if (write(fd, &object.y, sizeof(object.y)) <= 0)
        return (-2);
    if (write_str_to_file(fd, object.sprite->userdata) < 0)
        return (-3);
    return (0);
}
