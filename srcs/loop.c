/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badhont <badhont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 00:45:13 by lfatton           #+#    #+#             */
/*   Updated: 2019/04/18 10:35:10 by badhont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
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
#include "weapon.h"
#include "gun.h"
#include "enemies_intelligence.h"

static void loop_events(
        t_env *e,
        const Uint8 *state,
        t_timer_handler *timer_handler,
        enum e_bool *stop)
{
    SDL_Event 	ev;
    double		x;
    double		y;

    x = 0;
    y = 0;
    while (SDL_PollEvent(&ev))
	{
		if (ev.type == SDL_QUIT || state[SDL_SCANCODE_ESCAPE])
            *stop = e_true;
        if (!e->p.dead && !e->p.success)
        {
            if (ev.type == SDL_MOUSEBUTTONDOWN
            && ev.button.button == SDL_BUTTON_LEFT)
                e->p.weapon->main(e, timer_handler);
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

static void		select_enemy_sprite(t_enemy* enemy, t_coords pos)
{
    t_vector	view;
    t_vector	perpendicular_view;
    double		dot;

    if (enemy->time_in_death >= 0)
        return;
    view = (t_vector){enemy->object->x - pos.x, enemy->object->y - pos.y};
    normalize_vector(&view);
    dot = dot_product(&view, &enemy->heading);
    if (dot >= COS_PI_FOURTH)
        enemy->object->sprite = enemy->back;
    else if (dot <= -COS_PI_FOURTH)
        enemy->object->sprite = enemy->front;
    else
    {
        perpendicular_view = (t_vector){view.y, -view.x};
        dot = dot_product(&perpendicular_view, &enemy->heading);
        if (dot >= COS_PI_FOURTH)
            enemy->object->sprite = enemy->right;
        else if (dot <= -COS_PI_FOURTH)
            enemy->object->sprite = enemy->left;
    }
}

static void     update_enemies(t_sectors *sectors, t_coords camera_pos)
{
    int     i;
    t_linked_enemies	*enemies;
    t_linked_enemies	*next;

    i = 0;
    while (i < sectors->count)
    {
        enemies = sectors->items[i]->enemies;
        while (enemies)
        {
        	if (enemies->item.to_destroy)
			{
                next = enemies->next;
				delete_enemy(&sectors->items[i]->enemies, &enemies->item);
                enemies = next;
				continue;
			}
            select_enemy_sprite(&enemies->item, camera_pos);
            enemies = enemies->next;
        }
        i++;
    }
}

enum e_bool		update_logic(double ms_since_update, t_params params)
{
	t_logic_params	*ptr;

	ptr = (t_logic_params *)params;
	loop_events(ptr->e, ptr->state, ptr->timer_handler, ptr->stop);
	if (!ptr->e->p.dead && !ptr->e->p.success)
	    key_handler(ptr->state, &ptr->e->p, ptr->timer_handler);
    if (ptr->e->p.jump.height > 0)
    {
        ptr->e->p.jump.height -= ptr->e->p.jump.gravity * ms_since_update;
        ptr->e->p.jump.height = (ptr->e->p.jump.height < 1) ? 0 : ptr->e->p.jump.height;
    }
    update_enemies(ptr->map->sectors, ptr->e->p.pos);

    pick_objects(&ptr->e->p);
	//todo : if paused return t_false
	return (e_true);
}

t_logic_params		logic_params_init(
        t_env *e,
        const Uint8 *state,
        t_timer_handler *timer_handler,
        enum e_bool *stop)
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
    t_frame_event_params	params;

    params.e = e;
    params.map = e->map;
    params.time = 0;
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
            e->p.weapon->sprite_current,
            &e->p.weapon->main_animation,
            &e->op);
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

static void	init_game_loop(
        t_env *e,
        t_logic_params *update_logic_params,
        t_frame_event_params *frame_event_params,
        enum e_bool *stop)
{
    *stop = e_false;
	timer_handler_init(&e->timer_handler);
    *update_logic_params = logic_params_init(e, SDL_GetKeyboardState(NULL),
            &e->timer_handler, stop);
    *frame_event_params = frame_event_params_init(e);
    add_event(&e->timer_handler, 1, &update_logic, update_logic_params);
    add_event(&e->timer_handler, 1000.0 / e->op.fps_max, &frame_event,
            frame_event_params);
    add_event(&e->timer_handler, 30000, &day_to_night, &e->map->daytime);
    e->map->hud.id = 0;
    add_event(&e->timer_handler, 1000, &cross_index, &e->map->hud.id);
    add_event(&e->timer_handler, 5, &gun_idle_anim, get_weapon(e->p.weapons, 1));
    add_event(&e->timer_handler, 1000.0 / 60.0, &let_enemies_act, e);
    add_event(&e->timer_handler, 1000, &toggle_player_health, &e->p);
    Mix_PlayMusic(e->music, -1);
}

void		loop_doom(t_env *e)
{
    t_logic_params			update_logic_params;
    t_frame_event_params	frame_event_params;
    enum e_bool				stop;
    t_event					*n;
    t_event					*p;

    init_game_loop(e, &update_logic_params, &frame_event_params, &stop);
    while (!stop)
        update_events(&e->timer_handler);
    n = e->timer_handler.first;
    p = NULL;
    while (n)
    {
        p = n;
        n = n->next;
        p->function(1010000, p->params);
        free(p);
    }
}
