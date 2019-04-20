/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gun.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfatton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 08:31:09 by lfatton           #+#    #+#             */
/*   Updated: 2019/04/19 08:31:10 by lfatton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "weapon.h"
#include "doom.h"
#include "default.h"

enum e_bool	gun_idle_anim(double ms_since_update, t_params params)
{
	t_weapon	*gun;
	int			step;

	gun = (t_weapon *)params;
	if (!gun->main_ready)
		return (e_false);
	gun->animation.time += ms_since_update;
	if (gun->animation.time >= gun->animation.duration)
		gun->animation.time = 0;
	step = (int)(gun->animation.time) / (int)(gun->animation.duration / 3);
	if (step >= 3)
		step = 2;
	gun->sprite_current = gun->sprites[step];
	return (e_true);
}

enum e_bool	gun_firing(double ms_since_update, t_params params)
{
	t_weapon_and_timer	*ptr;

	ptr = (t_weapon_and_timer *)params;
	ptr->weapon->main_animation.time += ms_since_update;
	if (ptr->weapon->main_animation.time >= ptr->weapon->main_cooldown)
	{
		add_event(ptr->timer_handler, 5, &gun_idle_anim, ptr->weapon);
		free(ptr);
		return (e_false);
	}
	if (ptr->weapon->main_animation.time <= 200)
		ptr->weapon->sprite_current = ptr->weapon->sprites_fire;
	else
		ptr->weapon->sprite_current = ptr->weapon->sprites_cooldown;
	return (e_true);
}

void		gun_primary(t_env *e, t_timer_handler *timer_handler)
{
	t_weapon_and_timer	*params;
	t_weapon			*weapon;

	weapon = e->p.weapon;
	if (!weapon->main_ready || !weapon->ammo)
		return ;
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
	add_event(timer_handler, 1, &gun_firing, params);
	add_event(timer_handler, weapon->main_cooldown, &unlock,
			&weapon->main_ready);
}

void		load_gun_sprites(t_weapon *weapon, t_map *map)
{
	Uint32	i;

	i = 0;
	while (i < 3)
	{
		weapon->sprites[i] = map->gun_sprites[i];
		i++;
	}
	weapon->sprite_current = weapon->sprites[0];
	weapon->sprites_fire = map->gun_sprites[3];
	weapon->sprites_cooldown = map->gun_sprites[4];
}

t_weapon	*load_gun(t_sounds *sounds, t_map *map)
{
	t_weapon *gun;

	if (!(gun = (t_weapon *)malloc(sizeof(t_weapon))))
		error_doom("Couldn't malloc gun");
	load_gun_sprites(gun, map);
	gun->ammo = 0;
	gun->main = NULL;
	gun->usable = e_false;
	reset_animation(&gun->animation);
	gun->animation.duration = 500;
	gun->main = gun_primary;
	gun->main_cooldown = 500;
	reset_animation(&gun->main_animation);
	gun->main_ready = e_true;
	if (!(gun->main_sound = sounds->zap))
		error_doom("Can't load gun sound ...");
	gun->range = HORIZON;
	gun->scatter = 2;
	gun->scatter_angle = 2;
	gun->damage = 30;
	return (gun);
}
