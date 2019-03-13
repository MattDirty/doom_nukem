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

static void move_if_allowed(t_player *p, t_sector *sector, t_vector *direction, double scalar)
{
    scalar_multiply(direction, scalar);
    if (check_collision(sector, p, direction) > PLAYER_THICKNESS)
    {
        p->pos.x = p->pos.x + direction->x;
        p->pos.y = p->pos.y + direction->y;
    }
}

void		move(t_player *p, t_sector *sector, const Uint8 *state)
{
    t_vector    direction;

    if (state[SDL_SCANCODE_W] || state[SDL_SCANCODE_UP])
        direction = create_vector(cos(p->heading), -sin(p->heading));
    else if (state[SDL_SCANCODE_S] || state[SDL_SCANCODE_DOWN])
        direction = create_vector(-cos(p->heading), sin(p->heading));
    move_if_allowed(p, sector, &direction, RUN);
    if (state[SDL_SCANCODE_A])
        direction = create_vector(cos(p->heading - ROT_90), -sin(p->heading - ROT_90));
    else if (state[SDL_SCANCODE_D])
        direction = create_vector(-cos(p->heading - ROT_90), sin(p->heading - ROT_90));
    move_if_allowed(p, sector, &direction, STRAFE);
}
