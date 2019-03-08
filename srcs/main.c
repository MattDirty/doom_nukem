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

int		main (int ac, char **av)
{
	t_env		*e;

	(void)ac;
	(void)av;
	if (!(e = (t_env*)malloc(sizeof(t_env))))
		error_doom("error: cannot allocate memory for struct env");
	if (!(e->p = (t_player*)malloc(sizeof(t_player))))
		error_doom("error: cannot allocate memory for struct player");
	if (!(e->r = (t_ray*)malloc(sizeof(t_ray))))
		error_doom("error: cannot allocate memory for struct ray");
	init_doom(e);
	loop_doom(e);
	return (EXIT_SUCCESS);
}
