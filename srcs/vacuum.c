/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vacuum.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfatton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 08:20:57 by lfatton           #+#    #+#             */
/*   Updated: 2019/04/18 08:20:58 by lfatton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "weapon.h"
#include "doom.h"
#include "default.h"

void    vacuum_primary(t_env *e, t_timer_handler *timer_handler)
{
    t_weapon            *weapon;

    weapon = e->p.weapon;
    if (!weapon->main_ready || !weapon->ammo)
        return;
    Mix_PlayChannel(-1, weapon->main_sound, 0);
    weapon->main_ready = e_false;
    weapon_ray_fire(e, timer_handler);
}

t_weapon    *load_vacuum(t_sounds *sounds, t_map *map)
{
    t_weapon    *vacuum;

    if (!(vacuum = (t_weapon *)malloc(sizeof(t_weapon))))
        error_doom("Couldn't malloc vacuum");
    vacuum->sprites[0] = map->vacuum_sprite;
    vacuum->sprites[1] = map->vacuum_sprite;
    vacuum->sprites[2] = map->vacuum_sprite;
    vacuum->sprites_cooldown = map->vacuum_sprite;
    vacuum->sprites_fire = map->vacuum_sprite;
    vacuum->sprite_current = vacuum->sprites[0];
    vacuum->ammo = -1;
    vacuum->usable = e_false;
    vacuum->main = vacuum_primary;
    vacuum->main_cooldown = 60000;
    vacuum->main_ready = e_true;
    reset_animation(&vacuum->main_animation);
    if (!(vacuum->main_sound = sounds->slurp))
        error_doom("Can't load vacuum sound ...");
    vacuum->range = HORIZON;
    vacuum->scatter = 30;
    vacuum->scatter_angle = 0.785398;
    vacuum->damage = 500000;
    return (vacuum);
}
