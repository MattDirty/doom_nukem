/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   horizontal_motion.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfatton <lfatton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 10:43:10 by lfatton           #+#    #+#             */
/*   Updated: 2019/04/09 19:17:27 by mtorsell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "collision.h"
#include "player.h"
#include "default.h"
#include <math.h>

static t_segment	get_segment_and_mod_speed(t_vector *speed, double speed_factor, double time, t_coords pos)
{
	t_vector new_vector;

	new_vector.x = speed->x;
	new_vector.y = speed->y;
	change_vector_magnitude(speed, speed_factor * RUN * time);
	change_vector_magnitude(&new_vector, speed_factor * RUN * time + PLAYER_THICKNESS);
	return (create_segment_from_position_and_vector(pos.x, pos.y, &new_vector));
}

static void	handle_collision_for_speed(
        t_player *p,
        t_collisions *collisions,
        double time)
{
	t_collisions	*ptr;

    if (!collisions)
        return;
	ptr = collisions;
	while (ptr->next)
	    ptr = ptr->next;
	if (ptr->item.type == ct_wall && ptr->item.d.wall
	&& ptr->item.d.wall->type == e_wall)
	{
		if (ptr->item.distance <= PLAYER_THICKNESS)
		{
            change_vector_magnitude(&p->speed, 0);
            return;
        }
		if (ptr->item.distance <= RUN * time + PLAYER_THICKNESS)
			change_vector_magnitude(&p->speed,
					fabs(ptr->item.distance) - PLAYER_THICKNESS);
	}
	ptr = collisions;
	while (ptr)
	{
		if (ptr->item.type == ct_wall
        && ptr->item.d.wall
		&& ptr->item.d.wall->type == e_portal
		&& ptr->item.distance < get_vector_length(&p->speed))
			p->current_sector = get_next_sector_addr(p->current_sector,
													 ptr->item.d.wall);
		ptr = ptr->next;
	}
}

static void	move_if_allowed(t_player *p, double time)
{
	t_collisions	*collisions;
	t_segment		seg;

	seg = get_segment_and_mod_speed(&p->speed, p->speed_factor, time, p->pos);
	find_ray_collisions(p->current_sector, &seg, &collisions);
    handle_collision_for_speed(p, collisions, time);
	p->pos.x += p->speed.x;
	p->pos.y += p->speed.y;
    free_collisions(collisions);
}

void		move(t_player *p, const Uint8 *state, double time)
{
	if (state[SDL_SCANCODE_LSHIFT])
		p->speed_factor = 3;
	else
		p->speed_factor = 1;
	if (state[SDL_SCANCODE_W])
		add_vector_to_vector(&p->speed, create_vector(cos(p->heading), -sin(p->heading)));
	else if (state[SDL_SCANCODE_S])
		add_vector_to_vector(&p->speed, create_vector(-cos(p->heading), sin(p->heading)));
	if (state[SDL_SCANCODE_A])
		add_vector_to_vector(&p->speed, create_vector(cos(p->heading - ROT_90), -sin(p->heading - ROT_90)));
	else if (state[SDL_SCANCODE_D])
		add_vector_to_vector(&p->speed, create_vector(-cos(p->heading - ROT_90), sin(p->heading - ROT_90)));
	if (p->speed.x != 0 || p->speed.y != 0)
		move_if_allowed(p, time);
	p->speed.x = 0;
	p->speed.y = 0;
}
