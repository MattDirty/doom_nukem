#include "doom.h"

int		main (int ac, char **av)
{
	t_env		*e;

	if (!(e = (t_env*)malloc(sizeof(t_env))))
		error_doom("error: cannot allocate memory for struct env");
	if (!(e->p = (t_player*)malloc(sizeof(t_player))))
		error_doom("error: cannot allocate memory for struct player");
	if (!(e->sector = (t_sector*)malloc(sizeof(t_sector))))
		error_doom("error: cannot allocate memory for struct sector");
	e->sector->seg_count = 8;
	if (!(e->doom = (t_sdl*)malloc(sizeof(t_sdl))))
		error_doom("error: cannot allocate memory for struct sdl");
	init_doom(e);
	if (!(e->sector->walls = (t_segment*)malloc(sizeof(t_segment) * e->sector->seg_count)))
	{
		error_doom("cannot allocate memory");
	}
	if (ac > 1 && ft_strcmp(av[1], "debug") == 0)
	{
		e->debug_mode = t_true;
		e->debug = debug_init(e->sector->walls, e->sector->seg_count, e->p);
	}
	e->sector->walls[0] = create_segment(0, 0, 5, 1);
	e->sector->walls[1] = create_segment(5, 1, 4, 3);
	e->sector->walls[2] = create_segment(4, 3, 5, 6);
	e->sector->walls[3] = create_segment(5, 6, 8, 8);
    e->sector->walls[4] = create_segment(8, 8, 9, 15);
    e->sector->walls[5] = create_segment(9, 15, 3, 15);
    e->sector->walls[6] = create_segment(3, 15, 4, 4);
    e->sector->walls[7] = create_segment(4, 4, 0, 0);
	e->sector->wall_height = 1;

    if (!(e->sector->wall_text = SDL_LoadBMP("brickwall.bmp")))
    	error_doom("there was an error while loading the BMP");
	loop_doom(e);
	return (EXIT_SUCCESS);
}