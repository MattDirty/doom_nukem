#include "doom.h"

void		print_segment(t_segment *s, char *str)
{
	printf("%s\nstart (x : %f y : %f) end(x : %f y : %f)\n", str, s->start.x, s->start.y, s->end.x, s->end.y);

}

t_vector	get_vector_from_segment(t_segment *segment)
{
	t_vector	vector;

	vector.pos = segment->start;
	vector.direction.x = segment->end.x - segment->start.x;
	vector.direction.y = segment->end.y - segment->start.y;
	return (vector);
}

double		get_segment_length(t_segment *s)
{
	double	length;

	length = sqrt((s->start.x - s->end.x) * (s->start.x - s->end.x))
					+ (s->start.y - s->end.y) * (s->start.y - s->end.y);
	return (length);
}

void		change_segment_length(t_segment *s, double length)
{
	double		origin_length;

	origin_length = sqrt((s->start.x - s->end.x) * (s->start.x - s->end.x))
			+ (s->start.y - s->end.y) * (s->start.y - s->end.y);
	length -= origin_length;
	s->end.x = s->end.x + (s->end.x - s->start.x) / origin_length * length;
	s->end.y = s->end.y + (s->end.y - s->start.y) / origin_length * length;
}

t_segment	create_segment(double x1, double y1, double x2, double y2)
{
	t_segment	a;

	a.start.x = x1;
	a.end.x = x2;
	a.start.y = y1;
	a.end.y = y2;
	return (a);
}
