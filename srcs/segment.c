#include "utils.h"
#include <math.h>
#include <stdio.h>

void print_segment(t_segment *s, char *str)
{
    printf("%s\nstart (x : %f y : %f) end(x : %f y : %f)\n", str, s->x1, s->y1, s->x2, s->y2); // nooorminette
}

void move_segment_at(t_segment *segment, double x, double y)
{
    t_coords swap;

    swap.x = segment->x1;
    swap.y = segment->y1;
    segment->x1 = x;
    segment->y1 = y;
    segment->x2 -= swap.x - x;
    segment->y2 -= swap.y - y;
}

t_vector get_vector_from_segment(t_segment *segment)
{
    t_vector vector;

    vector.x = segment->x2 - segment->x1;
    vector.y = segment->y2 - segment->y1;
    return (vector);
}

double get_segment_length(t_segment *s)
{
    double length;

    length = sqrt((s->x1 - s->x2) * (s->x1 - s->x2)
                  + (s->y1 - s->y2) * (s->y1 - s->y2));
    return (length);
}

void change_segment_length(t_segment *segment, double length)
{
    double origin_length;
    double delta_x;
    double delta_y;

    delta_x = segment->x1 - segment->x2;
    delta_y = segment->y1 - segment->y2;

    origin_length = sqrt(delta_x * delta_x + delta_y * delta_y);

    length -= origin_length;
    segment->x2 = segment->x2
                  + (segment->x2 - segment->x1) / origin_length * length;
    segment->y2 = segment->y2
                  + (segment->y2 - segment->y1) / origin_length * length;
}

t_segment create_segment(double x1, double y1, double x2, double y2)
{
    t_segment a;

    a.x1 = x1;
    a.x2 = x2;
    a.y1 = y1;
    a.y2 = y2;
    return (a);
}
