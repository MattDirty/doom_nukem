/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfatton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 11:50:17 by lfatton           #+#    #+#             */
/*   Updated: 2019/04/19 11:50:19 by lfatton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "timer_handler.h"
#include "loop.h"
#include "collision.h"
#include "ui.h"
#include "surface_manipulation.h"

enum e_bool				update_logic(double ms_since_update, t_params params)
{
	t_logic_params	*ptr;

	ptr = (t_logic_params *)params;
	loop_events(ptr->e, ptr->state, ptr->timer_handler, ptr->stop);
	if (!ptr->e->p.dead && !ptr->e->p.success)
		key_handler(ptr->state, &ptr->e->p, ptr->timer_handler);
	if (ptr->e->p.jump.height > 0)
	{
		ptr->e->p.jump.height -= ptr->e->p.jump.gravity * ms_since_update;
		ptr->e->p.jump.height = (
				ptr->e->p.jump.height < 1) ? 0 : ptr->e->p.jump.height;
	}
	update_enemies(ptr->map->sectors, ptr->e->p.pos);
	pick_objects(&ptr->e->p);
	return (e_true);
}

t_logic_params			logic_params_init(t_env *e, const Uint8 *state,
							t_timer_handler *timer_handler, enum e_bool *stop)
{
	t_logic_params	params;

	params.e = e;
	params.map = e->map;
	params.state = state;
	params.timer_handler = timer_handler;
	params.stop = stop;
	return (params);
}

t_frame_event_params	frame_event_params_init(t_env *e)
{
	t_frame_event_params params;

	params.e = e;
	params.map = e->map;
	params.time = 0;
	return (params);
}

enum e_bool				frame_event(double ms_since_update, t_params params)
{
	t_env					*e;
	t_map					*map;
	t_frame_event_params	*frame_event_params;

	frame_event_params = (t_frame_event_params *)params;
	e = frame_event_params->e;
	map = frame_event_params->map;
	raycasting(e);
	draw_weapon(e->doom.surface, e->p.weapon->sprite_current,
			&e->p.weapon->main_animation, &e->op);
	if (e->p.dead)
		game_over(e, e->fonts->horrendo120, e->doom.surface, &e->op);
	if (e->p.success)
		game_victory(e->fonts->horrendo120, e->doom.surface, &e->op);
	if (frame_event_params->time >= 500 || !frame_event_params->time)
	{
		frame_event_params->fps = floor(1 / ms_since_update * 1000);
		frame_event_params->time = 0;
	}
	ui_draw(e->doom.surface, map, frame_event_params->fps, e);
	print_surface(e->doom.renderer, e->doom.surface);
	frame_event_params->time += ms_since_update;
	return (e_true);
}
