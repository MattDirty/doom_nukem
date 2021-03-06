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
#include "horizontal_motion.h"

static t_segment	get_segment_and_mod_speed(t_vector *speed, t_coords pos)
{
	t_vector new_vector;

	new_vector.x = speed->x;
	new_vector.y = speed->y;
	change_vector_magnitude(&new_vector, get_vector_length(speed) + PLAYER_THICKNESS);
	return (create_segment_from_position_and_vector(pos.x, pos.y, &new_vector));
}

static void	handle_collision_for_speed(
        t_vector *speed,
        t_sector **current_sector,
        t_collisions *collisions)
{
	t_collisions	*node;

    if (!collisions)
        return;
	node = collisions;
	while (node->next)
	    node = node->next;
	if (node->item.type == ct_wall && node->item.d.wall
	&& node->item.d.wall->type != e_portal)
	{
		if (node->item.distance <= PLAYER_THICKNESS)
		{
            change_vector_magnitude(speed, 0);
            return;
        }
		if (node->item.distance <= get_vector_length(speed) + PLAYER_THICKNESS)
			change_vector_magnitude(speed,
					fabs(node->item.distance) - PLAYER_THICKNESS);
	}
	node = collisions;
	while (node)
	{
		if (node->item.type == ct_wall
        && node->item.d.wall
		&& node->item.d.wall->type == e_portal
		&& node->item.distance < get_vector_length(speed))
			*current_sector = get_next_sector_addr(*current_sector,
													 node->item.d.wall);
		node = node->next;
	}
}

t_coords	allowed_move(t_vector speed, t_coords position, t_sector **current_sector)
{
	t_collisions	*collisions;
	t_segment		seg;

	seg = get_segment_and_mod_speed(&speed, position);
	find_ray_collisions(*current_sector, &seg, &collisions);
    handle_collision_for_speed(&speed, current_sector, collisions);
    free_collisions(collisions);
    return ((t_coords){position.x + speed.x, position.y + speed.y});
}

void		move(t_player *p, const Uint8 *state, double time)
{
    double speed_factor;
    t_vector speed;

    speed_factor = 1;
	if (state[SDL_SCANCODE_LSHIFT])
		speed_factor = 3;
    speed_factor *= MS_TO_S * time;
	speed.x = 0;
	speed.y = 0;
	if (state[SDL_SCANCODE_W])
		add_vector_to_vector(&speed, create_vector(cos(p->heading), -sin(p->heading)));
	else if (state[SDL_SCANCODE_S])
		add_vector_to_vector(&speed, create_vector(-cos(p->heading), sin(p->heading)));
	if (state[SDL_SCANCODE_A])
		add_vector_to_vector(&speed, create_vector(cos(p->heading - ROT_90), -sin(p->heading - ROT_90)));
	else if (state[SDL_SCANCODE_D])
		add_vector_to_vector(&speed, create_vector(-cos(p->heading - ROT_90), sin(p->heading - ROT_90)));
    change_vector_magnitude(&speed, speed_factor);
	if (speed.x != 0 || speed.y != 0)
        p->pos = allowed_move(speed, p->pos, &p->current_sector);
}
