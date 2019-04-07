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
    new->item.distance = distance;
    new->item.inters = inters;
    return (new);
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
            new = add_collision(collisions, distance, inters);
            new->item.type = ct_object;
            new->item.d.object = sector->objects->items + i;
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

	i = 0;
	best_collision.distance = HORIZON;
	while (i < sector->walls->count)
	{
		if (segments_intersect(ray, &sector->walls->items[i]->segment, &inters)
			&& last_portal != sector->walls->items[i])
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
		i++;
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
	node = collisions;
	while (1)
	{
        find_objects_collisions_in_sector(sector, ray, node);
        if (!find_wall_collisions_in_sector(sector, ray, node, last_portal)
                || (*node)->item.d.wall->type == e_wall)
            break;
		last_portal = (*node)->item.d.wall;
		sector = get_next_sector_addr(sector, (*node)->item.d.wall);
        while ((*node)->next)
            *node = (*node)->next;
	}
    if (!*collisions)
        error_doom("find_ray_collisions found nothing");
}
