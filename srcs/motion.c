/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   motion.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfatton <lfatton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 10:43:10 by lfatton           #+#    #+#             */
/*   Updated: 2019/03/13 10:43:25 by lfatton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static void move_if_allowed(t_env *e, t_vector direction, double scalar)
{
    scalar_multiply(&direction, scalar);
    if (check_collision(e, direction) > WALL_THICKNESS)
    {
        e->p->pos.x = e->p->pos.x + direction.x;
        e->p->pos.y = e->p->pos.y + direction.y;
    }
}

void		move(t_env *e, const Uint8 *state)
{
    t_vector    direction;

    if (state[SDL_SCANCODE_W] || state[SDL_SCANCODE_UP])
    {
        direction = create_vector(cos(e->p->heading), -sin(e->p->heading));
        move_if_allowed(e, direction, RUN);
    }
    else if (state[SDL_SCANCODE_S] || state[SDL_SCANCODE_DOWN])
    {
        direction = create_vector(-cos(e->p->heading), sin(e->p->heading));
        move_if_allowed(e, direction, RUN);
    }
    if (state[SDL_SCANCODE_A])
    {
        direction = create_vector(cos(e->p->heading - ROT_90), -sin(e->p->heading - ROT_90));
        move_if_allowed(e, direction, STRAFE);
    }
    else if (state[SDL_SCANCODE_D])
    {
        direction = create_vector(-cos(e->p->heading - ROT_90), sin(e->p->heading - ROT_90));
        move_if_allowed(e, direction, STRAFE);
    }
}
