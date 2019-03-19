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

#include "collision.h"
#include "player.h"
#include "default.h"

static void move_if_allowed(t_player *p, t_map *map, double time)
{
    t_segment seg;
    t_vector wall_parallel;
    t_collision collision;
    t_collision collision2;
    double      rad;
    t_sector *sector;

    sector = &map->sectors->items[0];

    scalar_multiply(&p->speed, RUN * time);
    seg = create_segment_from_position_and_vector(p->pos.x, p->pos.y, &p->speed);
    change_segment_length(&seg, PLAYER_THICKNESS);
    collision = check_collision(sector, &seg);
    if (collision.distance <= PLAYER_THICKNESS)
    {
        wall_parallel = get_vector_from_segment(&collision.wall->segment);
        rad = get_rad_between_vectors(&p->speed, &wall_parallel);
        rotate_vector(&p->speed, rad);
        if (rad > ft_degtorad(100))
        {
            p->speed.x = -p->speed.x;
            p->speed.y = -p->speed.y;
        }
        else if (rad >= ft_degtorad(80))
            return;
        seg = create_segment_from_position_and_vector(p->pos.x, p->pos.y, &p->speed);
        change_segment_length(&seg, PLAYER_THICKNESS);
        collision2 = check_collision(sector, &seg);
        if (collision.distance != collision2.distance && collision2.distance <= PLAYER_THICKNESS)
            return;
    }
    p->pos.x += p->speed.x;
    p->pos.y += p->speed.y;
}

void		move(t_player *p, t_map* map, const Uint8 *state, double time)
{
    if (state[SDL_SCANCODE_W])
        add_vector_to_vector(&p->speed, create_vector(cos(p->heading), -sin(p->heading)));
    if (state[SDL_SCANCODE_S])
        add_vector_to_vector(&p->speed, create_vector(-cos(p->heading), sin(p->heading)));
    if (state[SDL_SCANCODE_A])
        add_vector_to_vector(&p->speed, create_vector(cos(p->heading - ROT_90), -sin(p->heading - ROT_90)));
    if (state[SDL_SCANCODE_D])
        add_vector_to_vector(&p->speed, create_vector(-cos(p->heading - ROT_90), sin(p->heading - ROT_90)));
    move_if_allowed(p, map, time);
    p->speed.x = 0;
    p->speed.y = 0;
}

void look_up_and_down(t_player *p, const Uint8 *state, double time)
{
    if (state[SDL_SCANCODE_UP])
        p->vision_height += ROT_Y * time;
    if (state[SDL_SCANCODE_DOWN])
        p->vision_height -= ROT_Y * time;
    p->vision_height > WIN_H ? p->vision_height = WIN_H : 0;
    p->vision_height < 0 ? p->vision_height = 0 : 0;
}
