#include "objects.h"

#include <unistd.h>

#include "textures.h"
#include "serialisation.h"
#include "doom.h"

t_segment perpendicular_segment_from_point(
        t_object *object,
        double point_of_view_x,
        double point_of_view_y)
{
    t_vector	view;
    t_vector	perpendicular_view;
    t_segment	segment;

    view.x = object->x - point_of_view_x;
    view.y = object->y - point_of_view_y;
    normalize_vector(&view);
    perpendicular_view.x = view.y;
    perpendicular_view.y = -view.x;
    scalar_multiply(&perpendicular_view, object->horizontal_size / 2.0);
    segment.x1 = object->x - perpendicular_view.x;
    segment.y1 = object->y - perpendicular_view.y;
    segment.x2 = object->x + perpendicular_view.x;
    segment.y2 = object->y + perpendicular_view.y;
    return (segment);
}

void free_objects(t_objects *objects)
{
    free(objects->items);
    free(objects);
}

void read_objects_from_file(int fd, t_textures *textures, t_objects **objects)
{
    int count;
    int i;

    if (!(*objects = (t_objects*)malloc(sizeof(t_objects))))
        error_doom("couldn't malloc t_objects");
    if (read(fd, &count, sizeof(count)) <= 0)
        error_doom("couldn't read objects count");
    (*objects)->count = count;
    if (!((*objects)->items = (t_object*)malloc(sizeof(t_object) * count)))
        error_doom("couldn't malloc t_objects->items");
    i = 0;
    while (i < (*objects)->count)
    {
        read_object_from_file(fd, textures, &(*objects)->items[i]);
        i++;
    }
}

void write_objects_to_file(int fd, t_objects *objects)
{
    int i;

    if (write(fd, &objects->count, sizeof(objects->count)) <= 0)
        error_doom("couldn't write objects count");
    i = 0;
    while (i < objects->count)
    {
        write_object_to_file(fd, objects->items[i]);
        i++;
    }
}

void read_object_from_file(int fd, t_textures *textures, t_object *object)
{
    if (read(fd, &object->can_give_bonus, sizeof(object->can_give_bonus)) <= 0)
        error_doom("couldn't read object bool can_give_bonus");
    if (read(fd, &object->x, sizeof(object->x)) <= 0)
        error_doom("couldn't read object x");
    if (read(fd, &object->y, sizeof(object->y)) <= 0)
        error_doom("couldn't read object y");
    if (read(fd, &object->z, sizeof(object->z)) <= 0)
        error_doom("couldn't read object z");
    if (read(fd, &object->horizontal_size, sizeof(object->horizontal_size)) <= 0)
        error_doom("couldn't read object horizontal_size");
    if (read(fd, &object->vertical_size, sizeof(object->vertical_size)) <= 0)
        error_doom("couldn't read object vertical_size");
    find_texture_from_file(fd, textures, &object->sprite);
}

void write_object_to_file(int fd, t_object object)
{
    if (write(fd, &object.can_give_bonus, sizeof(object.can_give_bonus)) <= 0)
        error_doom("couldn't write object bool can_give_bonus");
    if (write(fd, &object.x, sizeof(object.x)) <= 0)
        error_doom("couldn't write object x");
    if (write(fd, &object.y, sizeof(object.y)) <= 0)
        error_doom("couldn't write object y");
    if (write(fd, &object.z, sizeof(object.z)) <= 0)
        error_doom("couldn't write object z");
    if (write(fd, &object.horizontal_size, sizeof(object.horizontal_size)) <= 0)
        error_doom("couldn't write object horizontal_size");
    if (write(fd, &object.vertical_size, sizeof(object.vertical_size)) <= 0)
        error_doom("couldn't write object vertical_size");
    write_str_to_file(fd, object.sprite->userdata);
}
