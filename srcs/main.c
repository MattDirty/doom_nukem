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
	if (!(e->sector = (t_sector*)malloc(sizeof(t_sector))))
		error_doom("error: cannot allocate memory for struct sector");
	init_doom(e);
	e->sector->seg_count = 4;
	if (!(e->sector->walls = (t_segment*)malloc(sizeof(t_segment) * e->sector->seg_count)))
	{
		error_doom("cannot allocate memory");
	}

	e->sector->walls[0] = create_segment(0, 0, 5, 1);
	e->sector->walls[1] = create_segment(5, 1, 4, 3);
	e->sector->walls[2] = create_segment(4, 3, 2, 3);
	e->sector->walls[3] = create_segment(2, 3, 0, 0);

    e->debug = debug_init(e->sector->walls, e->sector->seg_count, e->p);
	loop_doom(e);
	return (EXIT_SUCCESS);
}