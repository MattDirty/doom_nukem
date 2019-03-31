#include "utils.h"
#include <math.h>
#include <stdio.h>

t_segment get_segment_from_vector(t_vector *vector)
{
    t_segment segment;

    segment.x1 = 0;
    segment.y1 = 0;
    segment.x2 = 0 + vector->x;
    segment.y2 = 0 + vector->y;
    return (segment);
}

void rotate_vector(t_vector *vector, double rad)
{
    double swap_x;

    swap_x = vector->x * cos(rad) - vector->y * sin(rad);
    vector->y = vector->x * sin(rad) + vector->y * cos(rad);
    vector->x = swap_x;
}

double dot_product(t_vector *vector1, t_vector *vector2)
{
    return (vector1->x * vector2->x + vector1->y * vector2->y);
}

double get_vector_length(t_vector *vector)
{
    return (sqrt(vector->x * vector->x + vector->y * vector->y));
}

void        change_vector_magnitude(t_vector *vector, double new_magnitude)
{
    double  old_magnitude;

    old_magnitude = get_vector_length(vector);
    vector->x = vector->x * new_magnitude / old_magnitude;
    vector->y = vector->y * new_magnitude / old_magnitude;
}

double get_rad_between_vectors(t_vector *vector1, t_vector *vector2)
{
    double len1;
    double len2;

    len1 = get_vector_length(vector1);
    len2 = get_vector_length(vector2);
    return (acos(dot_product(vector1, vector2) / (len1 * len2)));
}

void add_vector_to_vector(t_vector *vector, t_vector vector2)
{
    vector->x += vector2.x;
    vector->y += vector2.y;
}

void scalar_multiply(t_vector *vector, double scalar)
{
    vector->x *= scalar;
    vector->y *= scalar;
}

t_segment create_segment_from_position_and_vector(
        double x,
        double y,
        t_vector *v)
{
    t_segment segment;

    segment.x1 = x;
    segment.y1 = y;
    segment.x2 = x + v->x;
    segment.y2 = y + v->y;

    return (segment);
}

void print_vector(t_vector *vector, char *str)
{
    printf("%s\nx : %f y : %f \n", str, vector->x, vector->y);
}

t_vector create_vector(double x, double y)
{
    t_vector new_vector;

    new_vector.x = x;
    new_vector.y = y;
    return (new_vector);
}

