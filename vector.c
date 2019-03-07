#include "doom.h"

t_segment	get_segment_from_vector(t_vector *vector)
{
	t_segment	segment;

	segment.start = vector->pos;
	segment.end.x = vector->pos.x + vector->direction.x;
	segment.end.y = vector->pos.y + vector->direction.y;
	return (segment);
}

void		print_vector(t_vector *vector, char *str)
{
	printf("%s\nx : %f y : %f position(x : %f y : %f)\n", str, vector->direction.x, vector->direction.y, vector->pos.x, vector->pos.y);
}

void		move_vector_at(t_vector *vector, double x, double y)
{
	vector->pos.x = x;
	vector->pos.y = y;
}

t_vector	create_vector(double x, double y)
{
	t_vector	new_vector;

	new_vector.direction.x = x;
	new_vector.direction.y = y;
	new_vector.pos.x = 0;
	new_vector.pos.y = 0;
	return (new_vector);
}

t_vector	create_vector_at(double x, double y, double pos_x, double pos_y)
{
	t_vector	new_vector;

	new_vector = create_vector(x, y);
	move_vector_at(&new_vector, pos_x, pos_y);
	return (new_vector);
}