/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfatton <lfatton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 05:41:52 by lfatton           #+#    #+#             */
/*   Updated: 2019/04/12 05:44:11 by lfatton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOOM_H
# define DOOM_H

# include "SDL_mixer.h"
# include "libft.h"
# include "struct_sdl.h"
# include "e_bool.h"
# include "player.h"
# include "config.h"

typedef struct          s_env
{
        t_config        op;
	t_sdl		debug;
	enum e_bool	debug_mode;
        t_player        p;
        t_sdl           doom;
        t_map		*map;
        Mix_Music 	*music;
}                       t_env;

void		error_doom(char *err);
int		quit_doom(t_env *e);

void		loop_doom(t_env *e);

#endif
