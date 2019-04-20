/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfatton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 06:24:26 by lfatton           #+#    #+#             */
/*   Updated: 2019/04/19 06:24:28 by lfatton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "collision.h"
#include "default.h"

t_collisions		*add_collision(t_collisions **collisions, double distance,
						t_coords inters)
{
	t_collisions	*node;
	t_collisions	*new;

	if (!(new = (t_collisions *)malloc(sizeof(t_collisions))))
		error_doom("Allocation of t_collisions failed");
	new->next = NULL;
	new->item.distance = distance;
	new->item.inters = inters;
	if (!*collisions)
	{
		*collisions = new;
	}
	else
	{
		node = *collisions;
		while (node->next)
			node = node->next;
		node->next = new;
	}
	return (new);
}

static void			insert_collision2(t_collisions *new,
						t_collisions **collisions)
{
	t_collisions	*prev;
	t_collisions	*node;

	prev = *collisions;
	node = prev->next;
	while (node && new->item.distance > prev->item.distance)
	{
		prev = node;
		node = node->next;
	}
	if (!node)
		prev->next = new;
	else
	{
		prev->next = new;
		new->next = node;
	}
}

t_collisions		*insert_collision(t_collisions **collisions,
						double distance, t_coords inters)
{
	t_collisions	*new;

	if (!(new = (t_collisions *)malloc(sizeof(t_collisions))))
		error_doom("Allocation of t_collisions failed");
	new->next = NULL;
	new->item.distance = distance;
	new->item.inters = inters;
	if (!*collisions)
		*collisions = new;
	else if (new->item.distance < (*collisions)->item.distance)
	{
		new->next = *collisions;
		*collisions = new;
	}
	else
		insert_collision2(new, collisions);
	return (new);
}

void				find_enemies_collisions_in_sector(t_sector *sector,
						t_segment *ray, t_collisions **collisions)
{
	t_linked_enemies	*enemies;
	t_coords			inters;
	double				distance;
	t_segment			s;
	t_collisions		*new;

	enemies = sector->enemies;
	while (enemies)
	{
		s = perpendicular_segment_from_point(
				enemies->item.object,
				ray->x1,
				ray->y1);
		if (segments_intersect(ray, &s, &inters))
		{
			distance = get_distance_between_points(ray->x1, ray->y1, inters.x,
					inters.y);
			new = insert_collision(collisions, distance, inters);
			new->item.type = ct_enemy;
			new->item.d.enemy = &enemies->item;
			new->item.object_segment = s;
		}
		enemies = enemies->next;
	}
}

void				find_pickables_collisions_in_sector(t_sector *sector,
						t_segment *ray, t_collisions **collisions)
{
	t_pickables		*pickables;
	t_coords		inters;
	double			distance;
	t_segment		s;
	t_collisions	*new;

	pickables = sector->pickables;
	while (pickables)
	{
		s = perpendicular_segment_from_point(
				pickables->item.object,
				ray->x1,
				ray->y1);
		if (segments_intersect(ray, &s, &inters))
		{
			distance = get_distance_between_points(ray->x1, ray->y1, inters.x,
					inters.y);
			new = insert_collision(collisions, distance, inters);
			new->item.type = ct_pickable;
			new->item.d.pickable = &pickables->item;
			new->item.object_segment = s;
		}
		pickables = pickables->next;
	}
}
