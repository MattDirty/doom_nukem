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

static void move_if_allowed(t_player *p, t_sector *sector)
{
    t_vector    wall_parallel;
    double      distance;
    double      rad;

    scalar_multiply(&p->speed, RUN);
    distance = check_collision(sector, p, &p->speed);
    distance = check_collision(sector, p, &p->speed);
    distance = check_collision(sector, p, &p->speed);
    if (distance <= PLAYER_THICKNESS)
    {
        printf("%f\n", distance);
        wall_parallel = get_vector_from_segment(&sector->walls[sector->wall_id]);
        rad = get_rad_between_vectors(&p->speed, &wall_parallel);
        rotate_vector(&p->speed, rad);
        if (rad > ft_degtorad(93))
        {
            p->speed.x = -p->speed.x;
            p->speed.y = -p->speed.y;
        }
        else if (rad >= ft_degtorad(87))
        {
            p->speed.x = 0;
            p->speed.y = 0;
        }
    }
    p->pos.x += p->speed.x;
    p->pos.y += p->speed.y;
}

void		move(t_player *p, t_sector *sector, const Uint8 *state)
{
    if (state[SDL_SCANCODE_W] || state[SDL_SCANCODE_UP])
        add_vector_to_vector(&p->speed, create_vector(cos(p->heading), -sin(p->heading)));
    if (state[SDL_SCANCODE_S] || state[SDL_SCANCODE_DOWN])
        add_vector_to_vector(&p->speed, create_vector(-cos(p->heading), sin(p->heading)));
    if (state[SDL_SCANCODE_A])
        add_vector_to_vector(&p->speed, create_vector(cos(p->heading - ROT_90), -sin(p->heading - ROT_90)));
    if (state[SDL_SCANCODE_D])
        add_vector_to_vector(&p->speed, create_vector(-cos(p->heading - ROT_90), sin(p->heading - ROT_90)));
    move_if_allowed(p, sector);
    p->speed.x = 0;
    p->speed.y = 0;
}
