#ifndef DOOMNUKEM_LOOP_H
# define DOOMNUKEM_LOOP_H

# include "doom.h"
# include "map.h"
# include "SDL.h"
# include "timer_handler.h"

typedef struct	s_logic_params
{
	t_env			*e;
	t_map			*map;
	const Uint8		*state;
	t_timer_handler	*timer_handler;
}				t_logic_params;

#endif
