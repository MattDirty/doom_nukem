/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapon_ray_fire.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtorsell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/20 00:39:07 by mtorsell          #+#    #+#             */
/*   Updated: 2019/04/20 00:39:09 by mtorsell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "collision.h"
#include "weapon.h"
#include "gun.h"
#include "melee.h"

static t_collisions	*skip_portals(t_collisions *ptr)
{
	while (ptr
		&& ptr->item.type == ct_wall
		&& ptr->item.d.wall->type == e_portal)
		ptr = ptr->next;
	return (ptr);
}

void				weapon_ray_fire(t_env *e, t_timer_handler *timer_handler)
{
	t_ray			ray;
	t_collisions	*collisions;
	t_collisions	*ptr;
	Uint32			x;

	x = -1;
	ray.angle = e->p.heading - e->p.weapon->scatter_angle / 2;
	while (ray.angle <= e->p.heading + e->p.weapon->scatter_angle / 2)
	{
		ray.angle += e->p.weapon->scatter_angle / e->p.weapon->scatter;
		ray.vect = create_vector(cos(ray.angle), -sin(ray.angle));
		change_vector_magnitude(&ray.vect, e->p.weapon->range);
		ray.seg = create_segment_from_position_and_vector(e->p.pos.x,
				e->p.pos.y, &ray.vect);
		find_ray_collisions(e->p.current_sector, &ray.seg, &collisions);
		if (!collisions)
			continue;
		ptr = collisions;
		ptr = skip_portals(ptr);
		if (ptr && ptr->item.type == ct_enemy)
			dmg_enemy(e, timer_handler, ptr->item.d.enemy, e->p.weapon->damage);
		else if (ptr && ptr->item.type == ct_object && e->p.weapon->ammo == -1)
			fuck_flower(&e->p, ptr->item.d.object);
		free_collisions(collisions);
	}
}
