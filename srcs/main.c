#include "doom.h"

enum e_bool get_line_intersection(t_segment *a, t_segment *b,t_coords *inters)
{
	t_coords	delta_a;
	t_coords	delta_b;
	double 	s;
	double	t;

	delta_a.x = a->end.x - a->start.x;
	delta_a.y = a->end.y - a->start.y;
	delta_b.x = b->end.x - b->start.x;
	delta_b.y = b->end.y - b->start.y;
	s = (-delta_a.y * (a->start.x - b->start.x) + delta_a.x * (a->start.y - b->start.y)) / (-delta_b.x * delta_a.y + delta_a.x * delta_b.y);
	t = ( delta_b.x * (a->start.y - b->start.y) - delta_b.y * (a->start.x - b->start.x)) / (-delta_b.x * delta_a.y + delta_a.x * delta_b.y);
	if (s >= 0 && s <= 1 && t >= 0 && t <= 1)
	{
		inters->x = a->start.x + (t * delta_a.x);
		inters->y = a->start.y + (t * delta_a.y);
		return (t_true);
	}

	return (t_false);
}

int		main ()
{
	t_vector	a;
	t_vector	b;
	t_vector	c;
	t_vector	d;
	t_segment	a_seg;
	t_segment	b_seg;
	t_segment	c_seg;
	t_segment	d_seg;
	t_coords	inters;

	a = create_vector_at(5, 5, 0, 0);
	b = create_vector_at(-5, 5, 5, 0);
	c = create_vector_at(5, 0, 0, 5);
	d = create_vector_at(0, 4, 2, 0);
	a_seg = get_segment_from_vector(&a);
	b_seg = get_segment_from_vector(&b);
	c_seg = get_segment_from_vector(&c);
	d_seg = get_segment_from_vector(&d);
	print_segment(&a_seg, "Segment A : ");
	print_segment(&b_seg, "Segment B : ");
	if (get_line_intersection(&a_seg, &b_seg, &inters))
		printf("A and B segments intersect at : ( %f, %f)\n", inters.x, inters.y);
	else
		printf("A and B segments don't intersect.\n");
	if (get_line_intersection(&c_seg, &d_seg, &inters))
		printf("C and D segments intersect at : ( %f, %f)\n", inters.x, inters.y);
	else
		printf("C and D segments don't intersect.\n");
	change_segment_length(&a_seg, 1.0);
	change_segment_length(&b_seg, 1.0);
	print_segment(&a_seg, "Segment A : ");
	print_segment(&b_seg, "Segment B : ");
	if (get_line_intersection(&a_seg, &b_seg, &inters))
		printf("A and B segments intersect at : ( %f, %f)\n", inters.x, inters.y);
	else
		printf("A and B segments don't intersect.\n");
	change_segment_length(&a_seg, 300.0);
	change_segment_length(&b_seg, 900.0);
	print_segment(&a_seg, "Segment A : ");
	print_segment(&b_seg, "Segment B : ");
	if (get_line_intersection(&a_seg, &b_seg, &inters))
		printf("A and B segments intersect at : ( %f, %f)\n", inters.x, inters.y);
	else
		printf("A and B segments don't intersect.\n");
	return (0);
}