/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfatton <lfatton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 01:10:34 by lfatton           #+#    #+#             */
/*   Updated: 2019/03/13 11:58:05 by lfatton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "e_bool.h"
#include "libft.h"
#include <math.h>
#include "collision.h"
#include "player.h"
#include "default.h"
#include "doom.h"
#include "player.h"
#include "render.h"

static enum e_bool segments_intersect(
        t_segment *a, t_segment *b, t_coords *inters)
{
    t_coords delta_a;
    t_coords delta_b;
    double s;
    double t;

    delta_a.x = a->x2 - a->x1;
    delta_a.y = a->y2 - a->y1;
    delta_b.x = b->x2 - b->x1;
    delta_b.y = b->y2 - b->y1;
    s = (-delta_a.y * (a->x1 - b->x1) + delta_a.x * (a->y1 - b->y1))
            / (-delta_b.x * delta_a.y + delta_a.x * delta_b.y);
    t = (delta_b.x * (a->y1 - b->y1) - delta_b.y * (a->x1 - b->x1))
            / (-delta_b.x * delta_a.y + delta_a.x * delta_b.y);
    if (s >= 0 && s <= 1 && t >= 0 && t <= 1)
    {
        inters->x = a->x1 + (t * delta_a.x);
        inters->y = a->y1 + (t * delta_a.y);
        return (t_true);
    }
    return (t_false);
}

static void update_collisions_list(t_collision **collision, Uint32 i)
{
    Uint32      j;
    t_collision *updated;

    j = 0;
    if (!(updated = (t_collision *)malloc(sizeof(t_collision) * (i + 1))))
        error_doom("There was an issue while mallocing collisions");
    while (j < i)
    {
        updated[j] = collision[0][j];
        j++;
    }
    free(*collision);
    *collision = updated;
}

t_sector	*get_next_sector_addr(t_sector *current, t_wall *wall)
{
	if (wall->pointer.sector.sector1 == current)
		return (wall->pointer.sector.sector2);
	else if (wall->pointer.sector.sector2 == current)
		return (wall->pointer.sector.sector1);
	return (NULL);
}

static void		update_collision(t_collision *collision, double distance, t_coords inters, t_wall *wall)
{
	collision->distance = distance;
	collision->inters = inters;
	collision->wall = wall;
}

static enum e_bool	check_collision_in_sector(t_sector *sector, t_segment *seg, t_collision *collision, t_wall *last_portal)
{
	int 		i;
	t_coords	inters;
	double		distance;

	i = 0;
	collision->distance = HORIZON;
	while (i < sector->walls->count)
	{
		if (segments_intersect(seg, &sector->walls->items[i]->segment, &inters)
		&& last_portal != sector->walls->items[i])
		{
			if ((distance = get_distance_between_points(seg->x1, seg->y1, inters.x, inters.y)) < collision->distance)
				update_collision(collision, distance, inters, sector->walls->items[i]);
		}
		i++;
	}
	if (collision->distance >= HORIZON)
		return (t_false);
	return (t_true);
}

Uint32  check_collision(t_sector *sector, t_segment *seg, t_collision **collision)
{
	t_wall	*last_portal;
	Uint32  i;

	last_portal = NULL;
	i = 0;
    if (!(*collision = (t_collision *)malloc(sizeof(t_collision))))
        error_doom("Can't malloc collision");
	while (check_collision_in_sector(sector, seg, &collision[0][i], last_portal))
    {
        i++;
	    update_collisions_list(collision, i);
	    if (collision[0][i - 1].wall->type != wall)
        {
	        last_portal = collision[0][i - 1].wall;
	        sector = get_next_sector_addr(sector, collision[0][i - 1].wall);
        }
	    else
	        break;
    }
	return (i);
}

void			raycasting(t_env *e)
{
	t_vector	ray_vect;
	t_segment	ray_seg;
	double		ray_angle;
    Uint32      renderer_x;
    t_collision	*collision;
    Uint32      collisions_number;

    renderer_x = 0;
    collision = NULL;
    while (renderer_x < e->op.win_w)
    {
        clamp_player_values(&e->p, e->op);
        ray_angle = e->p.heading + atan(
                (renderer_x / e->op.half_w - 1) * e->op.tan_half_fov);
		ray_vect = create_vector(cos(ray_angle), -sin(ray_angle));
		change_vector_magnitude(&ray_vect, HORIZON);
		ray_seg = create_segment_from_position_and_vector(
				e->p.pos.x,
				e->p.pos.y,
				&ray_vect);
		if ((collisions_number = check_collision(e->p.current_sector, &ray_seg, &collision)))
            draw(e, ray_angle, collision[collisions_number - 1], renderer_x);
		renderer_x++;
	}
}
