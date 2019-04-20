/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfatton <lfatton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 00:12:03 by lfatton           #+#    #+#             */
/*   Updated: 2019/04/11 00:12:13 by lfatton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "player.h"
#include "default.h"
#include "config.h"
#include "ui.h"
#include "e_bool.h"
#include "player.h"

t_player	init_player(t_config *op, t_coords spawn, t_sector *starting_sector)
{
	t_player	p;

	p.vision_height = op->half_h;
	p.heading = EAST;
	p.current_sector = starting_sector;
	p.pos.x = spawn.x;
	p.pos.y = spawn.y;
	p.jump.ready = e_true;
	p.jump.height = 0;
	p.jump.gravity = 0.1;
	p.jump.duration = 400;
	p.jump.time = 0;
	p.dead = e_false;
	p.health = HEALTH_MAX;
	p.healed = e_false;
	p.hurt = e_false;
	p.success = e_false;
	return (p);
}

void		clamp_player_values(t_player *p, t_config op)
{
	while (p->heading >= CIRCLE)
		p->heading -= CIRCLE;
	while (p->heading < 0)
		p->heading += CIRCLE;
	p->vision_height > op.win_h ? p->vision_height = op.win_h : 0;
	p->vision_height < 0 ? p->vision_height = 0 : p->vision_height;
	if (p->health <= 0)
		p->dead = e_true;
	if (p->dead)
	{
		p->health = 0;
		p->hurt = e_false;
		p->healed = e_false;
	}
}

enum e_bool	toggle_player_health(double ms_since_update, t_params pointer)
{
	t_player	*p;

	(void)ms_since_update;
	p = (t_player *)pointer;
	p->hurt = e_false;
	p->healed = e_false;
	return (e_true);
}

void		draw_face(SDL_Surface *surface, t_hud *hud, t_player *p,
				t_config *op)
{
	t_i_coords	pos;

	pos.x = op->half_w + 275;
	pos.y = op->win_h - 75;
	if (!p->weapon->main_ready)
	{
		draw_on_screen(surface, hud->badass_face, pos, e_true);
		if (p->healed || p->success)
			draw_on_screen(surface, hud->sehr_happy_face, pos, e_true);
		return ;
	}
	if (p->hurt)
		draw_on_screen(surface, hud->hurt_face, pos, e_true);
	else if (p->health > 75)
		draw_on_screen(surface, hud->happy_face, pos, e_true);
	else if (p->health <= 75 && p->health >= 50)
		draw_on_screen(surface, hud->meh_face, pos, e_true);
	else if (p->health < 50 && p->health >= 1)
		draw_on_screen(surface, hud->sad_face, pos, e_true);
	else if (p->dead)
		draw_on_screen(surface, hud->dead_face, pos, e_true);
	if (p->success)
		draw_on_screen(surface, hud->sehr_happy_face, pos, e_true);
}
