/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vertical_motion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfatton <lfatton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 19:56:04 by lfatton           #+#    #+#             */
/*   Updated: 2019/04/05 19:56:26 by lfatton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "config.h"
#include "SDL.h"
#include "default.h"
#include "player.h"

enum e_bool    jumping(double ms_since_update, t_params pointer)
{
    int step;
    int value;
    t_jump *jump;
    t_player *p;

    p = (t_player*)pointer;
    jump = &p->jump;
    jump->time += ms_since_update;
    step = (int)(jump->time) / (int)(jump->duration / 2);
    value = (int)(jump->time) % (int)(jump->duration / 2);
    if (step == 0)
        jump->height = value * JUMP_MAX / (jump->duration / 2);
    else if (step == 1)
        jump->height = JUMP_MAX;

    return (jump->time <= jump->duration);
}

void look_around(t_player *p, const Uint8 *state, double time)
{
    if (state[SDL_SCANCODE_UP])
        p->vision_height += ROT_Y * time;
    if (state[SDL_SCANCODE_DOWN])
        p->vision_height -= ROT_Y * time;
    if (state[SDL_SCANCODE_LEFT])
        p->heading -= ROT_X * time;
    if (state[SDL_SCANCODE_RIGHT])
        p->heading += ROT_X * time;
}

