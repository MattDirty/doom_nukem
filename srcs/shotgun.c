/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shotgun.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfatton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 07:54:18 by lfatton           #+#    #+#             */
/*   Updated: 2019/04/18 07:54:20 by lfatton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "weapon.h"
#include "doom.h"
#include "default.h"

enum e_bool shotgun_firing(double ms_since_update, t_params params)
{
    t_weapon_and_timer  *ptr;

    ptr = (t_weapon_and_timer *)params;
    ptr->weapon->main_animation.time += ms_since_update;
    if (ptr->weapon->main_animation.time >= ptr->weapon->main_cooldown)
    {
        ptr->weapon->sprite_current = ptr->weapon->sprites[0];
        free (ptr);
        return (e_false);
    }
    if (ptr->weapon->main_animation.time <= 400)
        ptr->weapon->sprite_current = ptr->weapon->sprites_fire;
    else
        ptr->weapon->sprite_current = ptr->weapon->sprites_cooldown;
    return (e_true);
}

void    shotgun_primary(t_env *e, t_timer_handler *timer_handler)
{
    t_weapon_and_timer  *params;
    t_weapon            *weapon;

    weapon = e->p.weapon;
    if (!weapon->main_ready || !weapon->ammo)
        return;
    Mix_PlayChannel(-1, weapon->main_sound, 0);
    weapon->main_ready = e_false;
    weapon->ammo--;
    reset_animation(&weapon->main_animation);
    weapon->main_animation.duration = weapon->main_cooldown;
    if (!(params = (t_weapon_and_timer *)malloc(sizeof(t_weapon_and_timer))))
        error_doom("Couldn't malloc params for firing");
    params->weapon = weapon;
    params->timer_handler = timer_handler;
    weapon_ray_fire(e, timer_handler);
    add_event(timer_handler, 1, &shotgun_firing, params);
    add_event(timer_handler, weapon->main_cooldown, &unlock,
              &weapon->main_ready);
}

void        load_shotgun_sprites(t_weapon *weapon, t_map *map)
{
    Uint32  i;

    i = 0;
    weapon->sprites[0] = map->shotgun_sprites[0];
    weapon->sprite_current = weapon->sprites[0];
    weapon->sprites_fire = map->shotgun_sprites[2];
    weapon->sprites_cooldown = map->shotgun_sprites[1];
}

t_weapon    *load_shotgun(t_sounds *sounds, t_map *map)
{
    t_weapon    *shotgun;

    if (!(shotgun = (t_weapon *)malloc(sizeof(t_weapon))))
        error_doom("Couldn't malloc shotgun");
    load_shotgun_sprites(shotgun, map);
    shotgun->ammo = 5;
    shotgun->usable = e_false;
    reset_animation(&shotgun->animation);
    shotgun->animation.duration = 500;
    shotgun->main = shotgun_primary;
    shotgun->main_cooldown = 1500;
    reset_animation(&shotgun->main_animation);
    shotgun->main_ready = e_true;
    if (!(shotgun->main_sound = sounds->pew))
        error_doom("Can't load shotgun sound ...");
    shotgun->range = HORIZON;
    shotgun->scatter = 30;
    shotgun->scatter_angle = 0.785398;
    shotgun->damage = 90;
    return (shotgun);
}
