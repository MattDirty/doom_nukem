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

static void		update_collision(
        t_collision *collision,
        double distance,
        t_coords inters,
        t_wall *wall)
{
	collision->distance = distance;
	collision->inters = inters;
	collision->type = ct_wall;
    collision->d.wall = wall;
}

static enum e_bool	find_collisions_in_sector(
        t_sector *sector,
        t_segment *ray,
        t_collision *collision,
        t_wall *last_portal)
{
	int 		i;
	t_coords	inters;
	double		distance;

	i = 0;
	collision->distance = HORIZON;
	while (i < sector->walls->count)
	{
		if (segments_intersect(ray, &sector->walls->items[i]->segment, &inters)
			&& last_portal != sector->walls->items[i])
		{
			if ((distance = get_distance_between_points(
                    ray->x1,
                    ray->y1,
                    inters.x,
                    inters.y)) < collision->distance)
                update_collision(
                        collision,
                        distance,
                        inters,
                        sector->walls->items[i]);
		}
		i++;
	}
    return (collision->distance < HORIZON);
}

void		find_ray_collisions(
        t_sector *sector,
        t_segment *ray,
        t_collisions **collisions)
{
	t_wall			*last_portal;
	t_collisions	*node;

	last_portal = NULL;
	if (!(*collisions = (t_collisions *)malloc(sizeof(t_collisions))))
		error_doom("Allocation of t_collisions failed");
	node = *collisions;
    node->item.type = ct_wall;
	node->item.d.wall = NULL;
	node->next = NULL;
	while (find_collisions_in_sector(
                sector,
                ray,
                &node->item,
                last_portal)
			&& node->item.d.wall->type != e_wall)
	{
		last_portal = node->item.d.wall;
		sector = get_next_sector_addr(sector, node->item.d.wall);
		if (!(node->next = (t_collisions *)malloc(sizeof(t_collisions))))
			error_doom("Allocation of t_collisions failed");
		node = node->next;
        node->item.type = ct_wall;
		node->item.d.wall = NULL;
		node->next = NULL;
	}
}
