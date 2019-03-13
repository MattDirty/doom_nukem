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
    t_vector    wall_parallel;
    double      distance;

    distance = check_collision(sector, p, direction);
    if (distance > PLAYER_THICKNESS)
    {
        scalar_multiply(direction, scalar);
        p->pos.x += direction->x;
        p->pos.y += direction->y;
    }
    else if (distance < PLAYER_THICKNESS && distance >= 0)
    {
        wall_parallel = get_vector_from_segment(&sector->walls[sector->wall_id]);
        print_vector(&wall_parallel, "wall seg");
        printf("%d \n", sector->wall_id);
        scalar_multiply(&wall_parallel, scalar);
        p->pos.x += wall_parallel.x;
        p->pos.y += wall_parallel.y;
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
