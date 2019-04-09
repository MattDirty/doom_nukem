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

#include "SDL.h"
#include "player.h"

void    key_handler(const Uint8 *state, t_player *p, t_timer_handler *timer_handler)
{
    if (state[SDL_SCANCODE_X])
        p->weapons.list[p->weapons.current].secondary(p->weapons.list[p->weapons.current],
                timer_handler);
    if (state[SDL_SCANCODE_SPACE] && !p->jump.height)
    {
        p->jump.time = 0;
        add_event(timer_handler, 5, &jumping, p);
    }
    if (state[SDL_SCANCODE_E])
        p->dead = t_true;
    if (state[SDL_SCANCODE_J])
    {
        p->health -= 10;
        if (p->health <= 0)
            p->dead = t_true;
        printf("Current HP : %d\n", p->health);
    }
    if (state[SDL_SCANCODE_K])
    {
        p->health += 10;
        if (p->health >= 100)
            p->health = 100;
        printf("Current HP : %d\n", p->health);
    }
    move(p, state, timer_handler->ms_since_update);
    look_around(p, state, timer_handler->ms_since_update);
}
