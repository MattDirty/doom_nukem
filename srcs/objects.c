#include "objects.h"
#include "textures.h"
#include "doom.h"
#include "sectors.h"

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
    if (objects->count > 0)
		free(objects->items);
    free(objects);
}
