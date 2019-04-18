#include "utils.h"
#include "doom.h"
#include <math.h>
#include <stdio.h>
#include <unistd.h>

enum e_bool	segments_share_node(t_segment *s1, t_segment *s2)
{
	return ((fabs(s1->x1 - s2->x1) < 0.001 && fabs(s1->y1 - s2->y1) < 0.001)
			|| (fabs(s1->x2 - s2->x1) < 0.001 && fabs(s1->y2 - s2->y1) < 0.001)
			|| (fabs(s1->x2 - s2->x2) < 0.001 && fabs(s1->y2 - s2->y2) < 0.001)
			|| (fabs(s1->x1 - s2->x2) < 0.001 && fabs(s1->y1 - s2->y2) < 0.001)
			);
}

enum e_bool segments_intersect(t_segment *a, t_segment *b, t_coords *inters)
{
	t_coords delta_a;
	t_coords delta_b;
	double s;
	double t;

	delta_a.x = a->x2 - a->x1;
	delta_a.y = a->y2 - a->y1;
	delta_b.x = b->x2 - b->x1;
	delta_b.y = b->y2 - b->y1;
	s = (-delta_a.y * (a->x1 - b->x1) + delta_a.x * (a->y1 - b->y1))
		/ (-delta_b.x * delta_a.y + delta_a.x * delta_b.y);
	t = (delta_b.x * (a->y1 - b->y1) - delta_b.y * (a->x1 - b->x1))
		/ (-delta_b.x * delta_a.y + delta_a.x * delta_b.y);
	if (s >= 0 && s <= 1 && t >= 0 && t <= 1)
	{
		inters->x = a->x1 + (t * delta_a.x);
		inters->y = a->y1 + (t * delta_a.y);
		return (e_true);
	}
	return (e_false);
}

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

void			read_segment_from_file(int fd, t_segment *segment)
{
    if (read(fd, &(segment->x1), sizeof(segment->x1)) <= 0)
        error_doom("couldn't read segment x1");
    if (read(fd, &(segment->y1), sizeof(segment->y1)) <= 0)
        error_doom("couldn't read segment y1");
    if (read(fd, &(segment->x2), sizeof(segment->x2)) <= 0)
        error_doom("couldn't read segment x2");
    if (read(fd, &(segment->y2), sizeof(segment->y2)) <= 0)
        error_doom("couldn't read segment y2");
}

void			write_segment_to_file(int fd, t_segment *segment)
{
    if (write(fd, &(segment->x1), sizeof(segment->x1)) <= 0)
        error_doom("couldn't write segment x1");
    if (write(fd, &(segment->y1), sizeof(segment->y1)) <= 0)
        error_doom("couldn't write segment y1");
    if (write(fd, &(segment->x2), sizeof(segment->x2)) <= 0)
        error_doom("couldn't write segment x2");
    if (write(fd, &(segment->y2), sizeof(segment->y2)) <= 0)
        error_doom("couldn't write segment y2");
}
