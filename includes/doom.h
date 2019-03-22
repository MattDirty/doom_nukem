#ifndef DOOM_H
# define DOOM_H

# include "libft.h"
# include "struct_sdl.h"
# include "e_bool.h"
# include "player.h"
# include "config.h"

typedef struct          s_env
{
        t_config        op; // tions
		t_sdl			debug;
		enum e_bool     debug_mode;
        t_player        p;
        t_sdl           doom;
		SDL_Surface		*derp;
}                       t_env;

void		error_doom(char *err);
int			quit_doom(t_env *e);
void		init_doom(t_env *e);

void		loop_doom(t_env *e, t_map *map);

#endif
