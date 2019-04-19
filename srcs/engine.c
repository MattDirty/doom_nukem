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

#include <pthread.h>
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

t_sector	*get_next_sector_addr(t_sector *current, t_wall *wall)
{
	if (wall->to_infinity)
		return (NULL);
	if (wall->links.sector1 == current)
		return (wall->links.sector2);
	else if (wall->links.sector2 == current)
		return (wall->links.sector1);
	return (NULL);
}

void			*raycasting_thread(void *args)
{
	t_ray			ray;
    Uint32			renderer_x;
    t_collisions	*collisions;
    t_collisions	*ptr;
    t_raycasting_args *a;

    a = (t_raycasting_args*)args;
    renderer_x = a->start - 1;
	clamp_player_values(&a->e->p, a->e->op);
    while ((renderer_x += a->inc) < a->e->op.win_w)
    {
        ray.angle = a->e->p.heading + atan(
                (renderer_x / a->e->op.half_w - 1) * a->e->op.tan_half_fov);
		ray.vect = create_vector(cos(ray.angle), -sin(ray.angle));
		change_vector_magnitude(&ray.vect, HORIZON);
		ray.seg = create_segment_from_position_and_vector(a->e->p.pos.x,
		        a->e->p.pos.y, &ray.vect);
		find_ray_collisions(a->e->p.current_sector, &ray.seg, &collisions);
        if (!collisions)
            continue;
		ptr = collisions;
		while (ptr)
		{
			ptr->item.distance *= cos(a->e->p.heading - ray.angle);
			ptr = ptr->next;
		}
		draw(a->e, collisions, renderer_x);
		free_collisions(collisions);
	}
    return (NULL);
}

void		    *generate_blackhole_buffer(void *args)
{
    t_env	*e;
    Uint32	i;
    time_t		t;

    srand((unsigned) time(&t));
    e = (t_env*)args;
    i = 0;
    while (!e->blackhole_thread_stop)
    {
        e->blackhole_buffer[i] = rand() % 100 > e->p.health;
        i++;
        i %= e->op.win_w * e->op.win_h;
    }
    return (NULL);
}

void			start_generating_blackhole_buffer(t_env *e)
{
    if (!(e->blackhole_buffer = malloc(e->op.win_h * e->op.win_w)))
        error_doom("could not allocate the most important buffer");
    e->blackhole_thread_stop = e_false;
    pthread_create(&e->blackhole_thread, NULL, generate_blackhole_buffer, e);
}

void			raycasting(t_env *e)
{
    const int nb_threads = 3;
    t_raycasting_args args[nb_threads];
    pthread_t threads[nb_threads];
    int i;

    i = 0;
    while (i < nb_threads)
    {
        args[i] = (t_raycasting_args){i, nb_threads, e};
        pthread_create(&threads[i], NULL, raycasting_thread, &args[i]);
        i++;
    }
    i = 0;
    while (i < nb_threads)
    {
        pthread_join(threads[i], NULL);
        i++;
    }
}
