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
	const Uint8		*state;
	struct timespec start, end;

	state = SDL_GetKeyboardState(NULL);
	while (42)
	{
		clock_gettime(CLOCK_MONOTONIC_RAW, &start);
		debug_draw(&e->debug, e->sector->walls, e->sector->seg_count, e->p);
        raycasting(e);
        ui_draw(e->doom, e->p->weapon);
        print_surface(e->doom->renderer, e->doom->surface);
        loop_events(e, state);
        move(e->p, e->sector, state);
        look_up_and_down(e->p, state);
		clock_gettime(CLOCK_MONOTONIC_RAW, &end);
		uint64_t delta_us = (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_nsec - start.tv_nsec) / 1000;
		printf("it took : %lu ms to loop.\n", delta_us / 1000);
    }
}
