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

static enum e_bool segments_intersect(
		t_segment *a, t_segment *b, t_coords *inters)
{
	t_coords delta_a;
	t_coords delta_b;
	double s;
	double t;

	delta_a.x = a->x2 - a->x1;
	delta_a.y = a->y2 - a->y1;
	delta_b.x = b->x2 - b->x1;
	delta_b.y = b->y2 - b->y1;
	s = (-delta_a.y * (a->x1 - b->x1) + delta_a.x * (a->y1 - b->y1))
		/ (-delta_b.x * delta_a.y + delta_a.x * delta_b.y);
	t = (delta_b.x * (a->y1 - b->y1) - delta_b.y * (a->x1 - b->x1))
		/ (-delta_b.x * delta_a.y + delta_a.x * delta_b.y);
	if (s >= 0 && s <= 1 && t >= 0 && t <= 1)
	{
		inters->x = a->x1 + (t * delta_a.x);
		inters->y = a->y1 + (t * delta_a.y);
		return (t_true);
	}
	return (t_false);
}

t_segment	get_segment_and_mod_speed(t_vector *speed, double time, t_coords pos)
{
	t_vector new_vector;

	new_vector.x = speed->x;
	new_vector.y = speed->y;
	change_vector_magnitude(speed, RUN * time);
	change_vector_magnitude(&new_vector, RUN * time + PLAYER_THICKNESS);
	return (create_segment_from_position_and_vector(pos.x, pos.y, &new_vector));
}

void	move_if_allowed(t_player *p, double time)
{
	t_segment	seg;
	t_collision	*collision;
	Uint32      collision_ret;

	seg = get_segment_and_mod_speed(&p->speed, time, p->pos);
	collision = NULL;
    collision_ret = check_collision(p->current_sector, &seg, &collision);
	if (collision_ret > 0)
	{
		if (collision[0].wall->type == wall)
		{
			if (collision[0].distance <= PLAYER_THICKNESS)
				scalar_multiply(&p->speed, 0);
			else
				change_vector_magnitude(&p->speed,
						fabs(collision[0].distance - PLAYER_THICKNESS));
		}
        if (collision[0].wall && collision[0].wall->type == portal)
        {
            seg = create_segment_from_position_and_vector(
                    p->pos.x, p->pos.y, &p->speed);
            if (segments_intersect(
                    &seg, &collision[0].wall->segment, &collision[0].inters))
                p->current_sector = get_next_sector_addr(p->current_sector,
                                                         collision[0].wall);
        }
	}
	free(collision);
	p->pos.x += p->speed.x;
	p->pos.y += p->speed.y;
}

void		move(t_player *p, const Uint8 *state, double time)
{
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
