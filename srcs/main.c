#include "doom.h"

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
	e->seg_count = 4;
	if (!(e->walls = (t_segment*)malloc(sizeof(t_segment) * e->seg_count)))
		error_doom("cannot allocate memory");
	e->walls[0] = create_segment(-2, -1, 3, 0);;
	e->walls[1] = create_segment(3, 0, 2, 2);;
	e->walls[2] = create_segment(2, 2, 0, 2);;
	e->walls[3] = create_segment(0, 2, -2, -1);;
	debug_init(e->walls, e->seg_count);
	loop_doom(e);
	return (EXIT_SUCCESS);
}