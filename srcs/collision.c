#include <stdio.h>
#include "collision.h"
#include "default.h"

void			free_collisions(t_collisions *collisions)
{
	t_collisions	*buffer;

	while (collisions)
	{
		buffer = collisions->next;
		free(collisions);
		collisions = buffer;
	}
}

static t_collisions		*add_collision(
        t_collisions **collisions,
        double distance,
        t_coords inters)
{
    t_collisions	*node;
    t_collisions	*new;

    if (!(new = (t_collisions*)malloc(sizeof(t_collisions))))
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

static t_collisions		*insert_collision(
        t_collisions **collisions,
        double distance,
        t_coords inters)
{
    t_collisions	*node;
    t_collisions	*prev;
    t_collisions	*new;

    if (!(new = (t_collisions*)malloc(sizeof(t_collisions))))
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
    {
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
    return (new);
}

static void		find_enemies_collisions_in_sector(
        t_sector *sector,
        t_segment *ray,
        t_collisions **collisions)
{
    int			    i;
    t_coords	    inters;
    double		    distance;
    t_segment       s;
    t_collisions	*new;

    i = 0;
    while (i < sector->enemies->count)
    {
        s = perpendicular_segment_from_point(
                sector->enemies->items[i].object,
                ray->x1,
                ray->y1);
        if (segments_intersect(ray, &s, &inters))
        {
            distance = get_distance_between_points(
                    ray->x1,
                    ray->y1,
                    inters.x,
                    inters.y);
            new = insert_collision(collisions, distance, inters);
            new->item.type = ct_object;
            new->item.d.object = sector->enemies->items[i].object;
            new->item.object_segment = s;
        }
        i++;
    }
}

static void		find_objects_collisions_in_sector(
        t_sector *sector,
        t_segment *ray,
        t_collisions **collisions)
{
	int			i;
	t_coords	inters;
    double		distance;
    t_segment   s;
    t_collisions	*new;

	i = 0;
	while (i < sector->objects->count)
    {
        s = perpendicular_segment_from_point(
                sector->objects->items + i,
                ray->x1,
                ray->y1);
        if (segments_intersect(ray, &s, &inters))
        {
			distance = get_distance_between_points(
                    ray->x1,
                    ray->y1,
                    inters.x,
                    inters.y);
            new = insert_collision(collisions, distance, inters);
            new->item.type = ct_object;
            new->item.d.object = sector->objects->items + i;
            new->item.object_segment = s;
        }
	    i++;
    }
}

static enum e_bool	find_wall_collisions_in_sector(
        t_sector *sector,
        t_segment *ray,
        t_collisions **collisions,
        t_wall *last_portal)
{
	int 		i;
	t_coords	inters;
	double		distance;
    t_collision best_collision;
    t_collisions *new;

	i = -1;
	best_collision.distance = HORIZON;
	while (++i < sector->walls->count)
	{
		if (last_portal == sector->walls->items[i])
			continue;
		if (segments_intersect(ray, &sector->walls->items[i]->segment, &inters))
		{
			distance = get_distance_between_points(
                    ray->x1, ray->y1, inters.x, inters.y);
            if (distance < best_collision.distance)
            {
                best_collision.distance = distance;
                best_collision.inters = inters;
                best_collision.d.wall = sector->walls->items[i];
            }
		}
	}
    if (best_collision.distance >= HORIZON)
        return (t_false);
    new = add_collision(collisions, best_collision.distance, best_collision.inters);
    new->item.type = ct_wall;
    new->item.d.wall = best_collision.d.wall;
    return (t_true);
}

void		find_ray_collisions(
        t_sector *sector,
        t_segment *ray,
        t_collisions **collisions)
{
	t_wall			*last_portal;
	t_collisions	**node;

	last_portal = NULL;
	*collisions = NULL;
	node = collisions;
	while (1)
	{
        find_enemies_collisions_in_sector(sector, ray, node);
        find_objects_collisions_in_sector(sector, ray, node);
        if (!find_wall_collisions_in_sector(sector, ray, node, last_portal))
            break;
        while ((*node)->next)
            node = &(*node)->next;
        if ((*node)->item.d.wall->type == e_wall)
            break;
		last_portal = (*node)->item.d.wall;
		sector = get_next_sector_addr(sector, (*node)->item.d.wall);
        node = &(*node)->next;
	}
}
