/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtorsell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 01:25:21 by mtorsell          #+#    #+#             */
/*   Updated: 2019/04/19 02:32:16 by badhont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLLISION_H
# define COLLISION_H

# include "utils.h"
# include "walls.h"
# include "sectors.h"
# include "doom.h"
# include "objects.h"
# include "levers.h"
# include "enemies.h"

typedef struct			s_ray
{
	t_vector	vect;
	t_segment	seg;
	double		angle;
}						t_ray;

typedef	struct			s_collision
{
	double				distance;
	t_coords			inters;
	enum				e_collision_type
	{
		ct_wall,
		ct_enemy,
		ct_lever,
		ct_object,
		ct_pickable
	}					type;
	union				u_type_data
	{
		t_wall		*wall;
		t_object	*object;
		t_lever		*lever;
		t_enemy		*enemy;
		t_pickable	*pickable;
	}					d;
	t_segment			object_segment;
}						t_collision;

typedef struct			s_collisions
{
	t_collision			item;
	struct s_collisions	*next;
}						t_collisions;

typedef struct			s_raycasting_args
{
    int					start;
    int					inc;
    t_env		    	*e;
}						t_raycasting_args;

enum e_bool				segments_intersect(t_segment *a, t_segment *b,
							t_coords *inters);
void					find_ray_collisions(t_sector *sector, t_segment *ray,
							t_collisions **collisions);
t_sector				*get_next_sector_addr(t_sector *current, t_wall *wall);
void					raycasting(t_env *e);
void					free_collisions(t_collisions *collisions);
t_collisions			*add_collision(t_collisions **collisions,
							double distance, t_coords inters);
t_collisions			*insert_collision(t_collisions **collisions,
							double distance, t_coords inters);
void					find_enemies_collisions_in_sector(t_sector *sector,
							t_segment *ray, t_collisions **collisions);
void					find_pickables_collisions_in_sector(t_sector *sector,
							t_segment *ray, t_collisions **collisions);
void					start_generating_blackhole_buffer(t_env *e);

#endif
