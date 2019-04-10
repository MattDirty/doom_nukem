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
#include "collision.h"
#include "ui.h"
#include "e_bool.h"
#include "config.h"
#include "render.h"
#include "timer_handler.h"
#include "surface_manipulation.h"
#include "loop.h"

static void loop_events(
        t_env *e,
        const Uint8 *state,
        t_timer_handler *timer_handler)
{
    SDL_Event 	ev;
    double		x;
    double		y;

    x = 0;
    y = 0;
    while (SDL_PollEvent(&ev))
	{
		if (ev.type == SDL_QUIT || state[SDL_SCANCODE_ESCAPE])
			quit_doom(e);
        if (!e->p.dead)
        {
            if (ev.type == SDL_MOUSEBUTTONDOWN && ev.button.button == SDL_BUTTON_LEFT)
                e->p.weapons.list[e->p.weapons.current].main(&e->p.weapons.list[e->p.weapons.current], timer_handler);
            if (ev.type == SDL_MOUSEMOTION)
            {
                x += ev.motion.xrel;
                y += ev.motion.yrel;
            }
        }
	}
	e->p.heading += x * e->op.mouse_sensi * timer_handler->ms_since_update;
	e->p.vision_height -= y * 1000 * e->op.mouse_sensi
			* timer_handler->ms_since_update;
}

enum e_bool		update_logic(double ms_since_update, t_params params)
{
	t_logic_params	*ptr;

	ptr = (t_logic_params *)params;
	loop_events(ptr->e, ptr->state, ptr->timer_handler);
	if (!ptr->e->p.dead)
	    key_handler(ptr->state, &ptr->e->p, ptr->timer_handler);
    if (ptr->e->p.jump.height > 0)
    {
        ptr->e->p.jump.height -= ptr->e->p.jump.gravity * ms_since_update;
        ptr->e->p.jump.height = (ptr->e->p.jump.height < 1) ? 0 : ptr->e->p.jump.height;
    }
	//todo : if paused return t_false
	return (t_true);
}

void		*logic_params_init(t_env *e, const Uint8 *state, t_timer_handler *timer_handler)
{
	t_logic_params	*params;

	if (!(params = (t_logic_params *)malloc(sizeof(t_logic_params))))
		error_doom("Couldn't malloc t_logic_params struct");
	params->e = e;
	params->map = e->map;
	params->state = state;
	params->timer_handler = timer_handler;
	return ((void *)params);
}

t_frame_event_params	*frame_event_params_init(t_env *e)
{
    t_frame_event_params	*params;

    if (!(params = (t_frame_event_params*)malloc(sizeof(t_frame_event_params))))
        error_doom("Couldn't allocate memory for t_frame_event_params");
    params->e = e;
    params->map = e->map;
    params->time = 0;
    return (params);
}

enum e_bool		frame_event(double ms_since_update, t_params params)
{
    t_env   				*e;
    t_map					*map;
    t_frame_event_params	*frame_event_params;

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
    if (e->p.dead)
        game_over(e->doom.surface, &e->op);
    if (frame_event_params->time >= 500 || !frame_event_params->time)
    {
        frame_event_params->fps = floor(1 / ms_since_update * 1000);
        frame_event_params->time = 0;
    }
    ui_draw(e->doom.surface, map, frame_event_params->fps, e);
    print_surface(e->doom.renderer, e->doom.surface);
    frame_event_params->time += ms_since_update;
    return (t_true);
}

enum e_bool cross_index(double ms_since_update, t_params i)
{
    (void)ms_since_update;
    (*(int*)i)++;
    return (t_true);
}

void		loop_doom(t_env *e)
{
    const Uint8 			*state;
    t_timer_handler	   		timer_handler;
    void					*update_logic_params;
    t_frame_event_params	*frame_event_params;

	timer_handler_init(&timer_handler);
    state = SDL_GetKeyboardState(NULL);

	update_logic_params = logic_params_init(e, state, &timer_handler);
    frame_event_params = frame_event_params_init(e);

    add_event(&timer_handler, 1, &update_logic, update_logic_params);
    add_event(
            &timer_handler,
            1000.0 / e->op.fps_max,
            &frame_event,
            frame_event_params);
    add_event(&timer_handler, 30000, &day_to_night, &e->map->daytime);
    e->map->id = 0;
    add_event(&timer_handler, 1000, &cross_index, &e->map->id);
    Mix_PlayMusic(e->music, -1);
    while (42)
        update_events(&timer_handler);
}
