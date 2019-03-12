#include "doom.h"

t_segment	get_segment_from_vector(t_vector *vector)
{
	t_segment	segment;

    segment.x1 = 0;
    segment.y1 = 0;
    segment.x2 = 0 + vector->x;
    segment.y2 = 0 + vector->y;
    return (segment);
}

void        scalar_multiply(t_vector *vector, double scalar)
{
	vector->x *= scalar;
    vector->y *= scalar;
}

t_segment	create_segment_from_position_and_vector(
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

void		print_vector(t_vector *vector, char *str)
{
	printf("%s\nx : %f y : %f position(x : %f y : %f)\n", str, vector->x, vector->y, vector->x, vector->y);
}

t_vector	create_vector(double x, double y)
{
	t_vector	new_vector;

	new_vector.x = x;
	new_vector.y = y;
	return (new_vector);
}

