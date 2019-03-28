/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfatton <lfatton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 00:45:13 by lfatton           #+#    #+#             */
/*   Updated: 2019/03/08 13:40:55 by lfatton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "default.h"
#include "utils.h"
#include "debug.h"
#include "engine.h"
#include "ui.h"
#include "config.h"
#include "timer_handler.h"
#include "surface_manipulation.h"
#include "loop.h"

static void loop_events(
        t_env *e,
        const Uint8 *state,
        t_timer_handler *timer_handler)
{
    SDL_Event ev;

    while (SDL_PollEvent(&ev))
    {
        if (ev.type == SDL_QUIT || state[SDL_SCANCODE_ESCAPE])
            quit_doom(e);
        if (ev.type == SDL_MOUSEMOTION)
        {
            e->p.heading += ev.motion.xrel * e->op.mouse_sensi
                    * timer_handler->ms_since_update;
            e->p.vision_height -= ev.motion.yrel * 1000
                    * e->op.mouse_sensi * timer_handler->ms_since_update;
            e->p.vision_height > e->op.win_h ? e->p.vision_height = e->op.win_h : 0;
            e->p.vision_height < 0 ? e->p.vision_height = 0 : e->p.vision_height;
        }
        if (state[SDL_SCANCODE_LEFT])
            e->p.heading -= ROT_X * timer_handler->ms_since_update / 1000;
        if (state[SDL_SCANCODE_RIGHT])
            e->p.heading += ROT_X * timer_handler->ms_since_update / 1000;
        if (state[SDL_SCANCODE_SPACE])
            e->p.weapons.list[e->p.weapons.current].main(
                    &e->p.weapons.list[e->p.weapons.current],
                    timer_handler);
        if (state[SDL_SCANCODE_X])
            e->p.weapons.list[e->p.weapons.current].secondary(
                    &e->p.weapons.list[e->p.weapons.current],
                    timer_handler);
//        if (state[SDL_SCANCODE_O])
//            e->sector->wall_height -= 0.01;
//        if (state[SDL_SCANCODE_P])
//            e->sector->wall_height += 0.01;
//        e->sector->wall_height > HALF_H ? e->sector->wall_height = HALF_H : 0;
//        e->sector->wall_height < 0 ? e->sector->wall_height = 0 : 0;
    }
}

enum e_bool		update_logic(double ms_since_update, t_params params)
{
	t_logic_params	*ptr;

    (void)ms_since_update;
	ptr = (t_logic_params *)params;
	loop_events(ptr->e, ptr->state, ptr->timer_handler);
	move(&ptr->e->p, ptr->state, ptr->timer_handler->ms_since_update);
	look_up_and_down(&ptr->e->p, &ptr->e->op, ptr->state, ptr->timer_handler->ms_since_update);
	//todo : if paused return t_false
	return (t_true);
}

void		*logic_params_init(t_env *e, t_map *map, const Uint8 *state, t_timer_handler *timer_handler)
{
	t_logic_params	*params;

	if (!(params = (t_logic_params *)malloc(sizeof(t_logic_params))))
		error_doom("Couldn't malloc t_logic_params struct");
	params->e = e;
	params->map = map;
	params->state = state;
	params->timer_handler = timer_handler;
	return ((void *)params);
}

t_frame_event_params	*frame_event_params_init(t_env *e, t_map *map)
{
    t_frame_event_params	*params;

    if (!(params = (t_frame_event_params*)malloc(sizeof(t_frame_event_params))))
        error_doom("Couldn't allocate memory for t_frame_event_params");
    params->e = e;
    params->map = map;
    return (params);
}

enum e_bool		frame_event(double ms_since_update, t_params params)
{
    t_env   				*e;
    t_map					*map;
    t_frame_event_params	*frame_event_params;

    (void)ms_since_update;
    frame_event_params = (t_frame_event_params*)params;
    e = frame_event_params->e;
    map = frame_event_params->map;
    if (e->debug_mode)
        debug_draw(&e->debug, map, &e->p, &e->op);
    raycasting(e);
    draw_weapon(
            e->doom.surface,
            e->p.weapons.list[e->p.weapons.current].sprite,
            &e->p.weapons.list[e->p.weapons.current].animation,
            &e->op);
    ui_draw(&e->doom, &e->op);
    print_surface(e->doom.renderer, e->doom.surface);
    return (t_true);
}

void		loop_doom(t_env *e, t_map *map)
{
    const Uint8 			*state;
    t_timer_handler			timer_handler;
    void					*update_logic_params;
    t_frame_event_params	*frame_event_params;

	timer_handler_init(&timer_handler);
    state = SDL_GetKeyboardState(NULL);

	update_logic_params = logic_params_init(e, map, state, &timer_handler);
    frame_event_params = frame_event_params_init(e, map);

    add_event(&timer_handler, 0, &update_logic, update_logic_params);
    add_event(
            &timer_handler,
            1000.0 / e->op.fps_max,
            &frame_event,
            frame_event_params);

    while (42)
		update_events(&timer_handler);
}
