/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfatton <lfatton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 16:32:39 by lfatton           #+#    #+#             */
/*   Updated: 2019/04/08 16:32:41 by lfatton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <SDL.h>
#include "player.h"
#include "levers.h"

static void	change_weapon(const Uint8 *state, t_player *p)
{
	t_weapon *new_weapon;

	if (state[SDL_SCANCODE_1])
		p->weapon = get_weapon(p->weapons, 0);
	else if (state[SDL_SCANCODE_2])
	{
		new_weapon = get_weapon(p->weapons, 1);
		if (new_weapon->usable)
			p->weapon = new_weapon;
	}
	else if (state[SDL_SCANCODE_3])
	{
		new_weapon = get_weapon(p->weapons, 2);
		if (new_weapon->usable)
			p->weapon = new_weapon;
	}
	else if (state[SDL_SCANCODE_4])
	{
		new_weapon = get_weapon(p->weapons, 3);
		if (new_weapon->usable)
			p->weapon = new_weapon;
	}
}

void		key_handler(
				const Uint8 *state, t_player *p, t_timer_handler *timer_handler)
{
	if (state[SDL_SCANCODE_SPACE] && !p->jump.height)
	{
		p->jump.time = 0;
		add_event(timer_handler, 5, &jumping, p);
	}
	if (state[SDL_SCANCODE_E])
		use_lever_if_available(p, timer_handler);
	move(p, state, timer_handler->ms_since_update);
	look_around(p, state, timer_handler->ms_since_update);
	change_weapon(state, p);
}
