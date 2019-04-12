/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   melee.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfatton <lfatton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 06:08:24 by lfatton           #+#    #+#             */
/*   Updated: 2019/04/12 06:08:25 by lfatton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "animation.h"
#include "weapon.h"
#include "timer_handler.h"
#include "e_bool.h"

enum e_bool    unlock(double ms_since_update, t_params ready)
{
    (void)ms_since_update;
    *(enum e_bool*)ready = t_true;
    return (t_false);
}

enum e_bool    melee_primary_animation(
        double ms_since_update,
        t_params pointer)
{
    int step;
    int value;
    t_animation *animation;

    animation = (t_animation*)pointer;
    animation->time += ms_since_update;

    step = (int)(animation->time) / (int)(animation->duration / 4);
    value = (int)(animation->time) % (int)(animation->duration / 4);
    if (step == 0)
        animation->x_offset = -value;
    if (step == 1)
        animation->x_offset = -(animation->duration / 4) + value;
    if (step == 2)
        animation->x_offset = value;
    if (step == 3)
        animation->x_offset = animation->duration / 4 - value;
    if (step > 3)
        animation->x_offset = 0;

    return (animation->time <= animation->duration);
}

void    melee_secondary(t_weapon *weapon, t_timer_handler *timer_handler)
{
    if (!weapon->secondary_ready)
        return;
    weapon->secondary_ready = t_false;
    add_event(
            timer_handler,
            weapon->secondary_cooldown,
            &unlock,
            &weapon->secondary_ready);
}

void    melee_primary(t_weapon *weapon, t_timer_handler *timer_handler)
{
    if (!weapon->main_ready || !weapon->ammo)
        return;

    reset_animation(&weapon->animation);
    start_animation(&weapon->animation, 400);
    add_event(
            timer_handler,
            5,
            &melee_primary_animation,
            &weapon->animation);
    Mix_PlayChannel(-1, weapon->main_sound, 0);
    weapon->main_ready = t_false;
    weapon->ammo--;
    add_event(
            timer_handler,
            weapon->main_cooldown,
            &unlock,
            &weapon->main_ready);
}
