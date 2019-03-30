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

static void move_if_allowed(t_player *p, double time)
{
	t_segment	seg;
	t_vector	wall_parallel;
	t_collision	collision[2];
	t_sector	*sector;
	double		rad;

	sector = p->current_sector;
	scalar_multiply(&p->speed, RUN * time);
	seg = create_segment_from_position_and_vector(p->pos.x, p->pos.y, &p->speed);
	change_segment_length(&seg, PLAYER_THICKNESS);
	if (check_collision(sector, &seg, &collision[0]))
	{
		if (collision[0].wall && collision[0].wall->type == wall
			&& collision[0].distance <= RUN * time + PLAYER_THICKNESS)
		{
			wall_parallel = get_vector_from_segment(
					&collision[0].wall->segment);
			rad = get_rad_between_vectors(&p->speed, &wall_parallel);
			if (rad <= RAD_DEG_100 && rad >= RAD_DEG_80)
				return;
			rotate_vector(&p->speed, rad);
			if (rad < RAD_DEG_80)
			{
				p->speed.x = -p->speed.x;
				p->speed.y = -p->speed.y;
			}
			seg = create_segment_from_position_and_vector(p->pos.x, p->pos.y,
														  &p->speed);
			change_segment_length(&seg, PLAYER_THICKNESS);
			if (check_collision(sector, &seg, &collision[1]))
			{
				if (collision[1].wall && collision[1].wall->type == wall
					&& collision[0].distance != collision[1].distance
					&& collision[1].distance <= RUN * time + PLAYER_THICKNESS)
					return;
			}
		}
		if ((collision[0].wall && collision[0].wall->type == portal))
		{
			p->current_sector = collision[0].wall->pointer.sector.sector2;
			collision[0].wall->pointer.sector.sector2 = collision[0].wall->pointer.sector.sector1;
			collision[0].wall->pointer.sector.sector1 = p->current_sector;
		}
	}
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
	if (p->speed.x || p->speed.y)
		move_if_allowed(p, time);
	p->speed.x = 0;
	p->speed.y = 0;
}

void look_up_and_down(t_player *p, t_config *op, const Uint8 *state, double time)
{
	if (state[SDL_SCANCODE_UP])
		p->vision_height += ROT_Y * time;
	if (state[SDL_SCANCODE_DOWN])
		p->vision_height -= ROT_Y * time;
	p->vision_height > op->win_h ? p->vision_height = op->win_h : 0;
	p->vision_height < 0 ? p->vision_height = 0 : 0;
}
