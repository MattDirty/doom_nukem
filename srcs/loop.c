/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfatton <lfatton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 00:45:13 by lfatton           #+#    #+#             */
/*   Updated: 2019/03/08 13:40:55 by lfatton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static void	loop_events(t_env *e, const Uint8 *state)
{
	SDL_Event	ev;

	while (SDL_PollEvent(&ev))
	{
		if (ev.type == SDL_QUIT || state[SDL_SCANCODE_ESCAPE])
			quit_doom(e);
		if (ev.type == SDL_MOUSEMOTION)
		{
			e->p->heading += ev.motion.xrel * MOUSE_SENSI;
			e->p->vision_height -= ev.motion.yrel;
			e->p->vision_height > WIN_H ? e->p->vision_height = WIN_H : 0;
			e->p->vision_height < 0 ? e->p->vision_height = 0 : 0;
		}
		if (state[SDL_SCANCODE_LEFT])
			e->p->heading -= ROT_X;
		if (state[SDL_SCANCODE_RIGHT])
			e->p->heading += ROT_X;
		if (state[SDL_SCANCODE_O])
			e->sector->wall_height -= 0.01;
		if (state[SDL_SCANCODE_P])
			e->sector->wall_height += 0.01;
		e->sector->wall_height > HALF_H ? e->sector->wall_height = HALF_H : 0;
		e->sector->wall_height < 0 ? e->sector->wall_height = 0 : 0;
	}
}

void		loop_doom(t_env *e)
{
	const Uint8	*state;

	state = SDL_GetKeyboardState(NULL);
	while (42)
	{
        debug_draw(&e->debug, e->sector->walls, e->sector->seg_count, e->p);
        raycasting(e);
        print_surface(e->render, e->surf);
		loop_events(e, state);
        move(e->p, e->sector, state);
        look_up_and_down(e->p, state);
    }
}
