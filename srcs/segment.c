#include "doom.h"

void		print_segment(t_segment *s, char *str)
{
	printf("%s\nstart (x : %f y : %f) end(x : %f y : %f)\n", str, s->x1, s->y1, s->x2, s->y2);

}

enum e_bool segments_intersect(t_segment *a, t_segment *b,t_coords *inters)
{
	t_coords	delta_a;
	t_coords	delta_b;
	double 	s;
	double	t;

	delta_a.x = a->x2 - a->x1;
	delta_a.y = a->y2 - a->y1;
	delta_b.x = b->x2 - b->x1;
	delta_b.y = b->y2 - b->y1;
	s = (-delta_a.y * (a->x1 - b->x1) + delta_a.x * (a->y1 - b->y1)) / (-delta_b.x * delta_a.y + delta_a.x * delta_b.y);
	t = ( delta_b.x * (a->y1 - b->y1) - delta_b.y * (a->x1 - b->x1)) / (-delta_b.x * delta_a.y + delta_a.x * delta_b.y);
	if (s >= 0 && s <= 1 && t >= 0 && t <= 1)
	{
		inters->x = a->x1 + (t * delta_a.x);
		inters->y = a->y1 + (t * delta_a.y);
		return (t_true);
	}

	return (t_false);
}

t_vector	get_vector_from_segment(t_segment *segment)
{
	t_vector	vector;

	vector.pos.x = segment->x1;
	vector.pos.y = segment->y1;
	vector.direction.x = segment->x2 - segment->x1;
	vector.direction.y = segment->y2 - segment->y1;
	return (vector);
}

double		get_segment_length(t_segment *s)
{
	double	length;

	length = sqrt((s->x1 - s->x2) * (s->x1 - s->x2))
					+ (s->y1 - s->y2) * (s->y1 - s->y2);
	return (length);
}

void		change_segment_length(t_segment *s, double length)
{
	double		origin_length;

	origin_length = sqrt((s->x1 - s->x2) * (s->x1 - s->x2))
			+ (s->y1 - s->y2) * (s->y1 - s->y2);
	length -= origin_length;
	s->x2 = s->x2 + (s->x2 - s->x1) / origin_length * length;
	s->y2 = s->y2 + (s->y2 - s->y1) / origin_length * length;
}

t_segment	create_segment(double x1, double y1, double x2, double y2)
{
	t_segment	a;

	a.x1 = x1;
	a.x2 = x2;
	a.y1 = y1;
	a.y2 = y2;
	return (a);
}