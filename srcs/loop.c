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
#include "surface_manipulation.h"

static void loop_events(t_env *e, const Uint8 *state, double time)
{
    SDL_Event ev;

    while (SDL_PollEvent(&ev))
    {
        if (ev.type == SDL_QUIT || state[SDL_SCANCODE_ESCAPE])
            quit_doom(e);
        if (ev.type == SDL_MOUSEMOTION)
        {
            e->p->heading += ev.motion.xrel * MOUSE_SENSI * time;
            e->p->vision_height -= ev.motion.yrel * time;
            e->p->vision_height > WIN_H ? e->p->vision_height = WIN_H : 0;
            e->p->vision_height < 0 ? e->p->vision_height = 0 : 0;
        }
        if (state[SDL_SCANCODE_LEFT])
            e->p->heading -= ROT_X * time;
        if (state[SDL_SCANCODE_RIGHT])
            e->p->heading += ROT_X * time;
//        if (state[SDL_SCANCODE_O])
//            e->sector->wall_height -= 0.01;
//        if (state[SDL_SCANCODE_P])
//            e->sector->wall_height += 0.01;
//        e->sector->wall_height > HALF_H ? e->sector->wall_height = HALF_H : 0;
//        e->sector->wall_height < 0 ? e->sector->wall_height = 0 : 0;
    }
}

void		loop_doom(t_env *e, t_map *map)
{
    const Uint8 *state;
    struct timespec start;
    struct timespec end;
    double ms_since_frame;
    double ms_since_move;

    state = SDL_GetKeyboardState(NULL);
    ms_since_frame = 1000;
    ms_since_move = 0;
    while (42)
    {
        clock_gettime(CLOCK_MONOTONIC_RAW, &start);
        loop_events(e, state, ms_since_move);
        move(e->p, map, state, ms_since_move);
        look_up_and_down(e->p, state, ms_since_move);
        if (ms_since_frame >= 1000.0 / FPS_MAX)
        {
            if (e->debug_mode)
                debug_draw(&e->debug, map, e->p);
            raycasting(e, map);
            draw_weapon(e->doom->surface, e->p->weapons.list[e->p->weapons.current].sprite);
            ui_draw(e->doom);
            print_surface(e->doom->renderer, e->doom->surface);
            ms_since_frame = 0;
        }
        clock_gettime(CLOCK_MONOTONIC_RAW, &end);
        ms_since_move = delta_ms(start, end);
        ms_since_frame += delta_ms(start, end);
    }
}
