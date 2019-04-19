/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfatton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 06:41:37 by lfatton           #+#    #+#             */
/*   Updated: 2019/04/19 06:41:41 by lfatton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "collision.h"
#include "default.h"

static void			find_objects_collisions_in_sector(t_sector *sector,
		t_segment *ray, t_collisions **collisions)
{
	int				i;
	t_coords		inters;
	double			dist;
	t_segment		s;
	t_collisions	*new;

	i = 0;
	while (i < sector->objects->count)
	{
		s = perpendicular_segment_from_point(sector->objects->items + i,
				ray->x1, ray->y1);
		if (segments_intersect(ray, &s, &inters))
		{
			dist = get_dist_between_points(ray->x1, ray->y1, inters.x,
					inters.y);
			new = insert_collision(collisions, dist, inters);
			new->item.type = ct_object;
			new->item.d.object = sector->objects->items + i;
			new->item.object_segment = s;
		}
		i++;
	}
}

static void			find_lever_collisions(t_collisions **collisions,
		t_wall *wall, double dist, t_coords inters)
{
	t_lever			*lever;
	double			offset_on_wall;
	t_collisions	*new;

	if (dist < P_THICK)
		return ;
	if (!(lever = wall->lever) || lever->wall_object == NULL)
		return ;
	offset_on_wall = get_dist_between_points(wall->segment.x1,
			wall->segment.y1, inters.x, inters.y);
	if (offset_on_wall < wall->lever->wall_object->offset_on_wall
		|| offset_on_wall >= lever->wall_object->offset_on_wall
		+ lever->wall_object->size)
		return ;
	new = add_collision(collisions, dist, inters);
	new->item.type = ct_lever;
	new->item.d.lever = lever;
}

static enum e_bool	find_wall_collisions_in_sector(t_sector *sector,
		t_segment *ray, t_collisions **collisions, t_wall *last_portal)
{
	int				i;
	t_coords		inters;
	double			dist;
	t_collision		best_collision;
	t_collisions	*new;

	i = -1;
	best_collision.dist = HORIZON;
	while (++i < sector->walls->count)
	{
		if (last_portal == sector->walls->items[i])
			continue ;
		if (segments_intersect(ray, &sector->walls->items[i]->segment, &inters))
		{
			dist = get_dist_between_points(ray->x1, ray->y1, inters.x,
					inters.y);
			if (dist < best_collision.dist)
			{
				best_collision.dist = dist;
				best_collision.inters = inters;
				best_collision.d.wall = sector->walls->items[i];
			}
			find_lever_collisions(collisions, sector->walls->items[i], dist,
					inters);
		}
	}
	if (best_collision.dist >= HORIZON)
		return (e_false);
	if (best_collision.d.wall->type == e_wall)
		new = insert_collision(collisions, best_collision.dist,
				best_collision.inters);
	else
		new = add_collision(collisions, best_collision.dist,
				best_collision.inters);
	new->item.type = ct_wall;
	new->item.d.wall = best_collision.d.wall;
	if (new->item.d.wall->type == e_wall)
	{
		free_collisions(new->next);
		new->next = NULL;
	}
	return (e_true);
}

void				find_ray_collisions(t_sector *sector, t_segment *ray,
		t_collisions **collisions)
{
	t_wall			*last_portal;
	t_collisions	**n;

	last_portal = NULL;
	*collisions = NULL;
	n = collisions;
	while (1)
	{
		find_enemies_collisions_in_sector(sector, ray, n);
		find_objects_collisions_in_sector(sector, ray, n);
		find_pickables_collisions_in_sector(sector, ray, n);
		if (!find_wall_collisions_in_sector(sector, ray, n, last_portal))
			break ;
		while ((*n)->next)
			n = &(*n)->next;
		if ((*n)->item.d.wall->type == e_wall || (*n)->item.d.wall->to_infinity)
			break ;
		last_portal = (*n)->item.d.wall;
		sector = get_next_sector_addr(sector, (*n)->item.d.wall);
		n = &(*n)->next;
	}
}
