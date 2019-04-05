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

static void		update_collision(t_collision *collision, double distance, t_coords inters, t_wall *wall)
{
	collision->distance = distance;
	collision->inters = inters;
	collision->wall = wall;
}

static enum e_bool	check_collision_in_sector(t_sector *sector, t_segment *seg, t_collision *collision)
{
	int 		i;
	t_coords	inters;
	double		distance;

	i = 0;
	collision->distance = HORIZON;
	while (i < sector->walls->count)
	{
		if (segments_intersect(seg, &sector->walls->items[i]->segment, &inters)
			&& collision->last_portal != sector->walls->items[i])
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

void		check_collision(t_sector *sector, t_segment *seg, t_collisions **first)
{
	t_wall			*last_portal;
	t_collisions	*collisions;

	last_portal = NULL;
	if (!(*first = (t_collisions *)malloc(sizeof(t_collisions))))
		error_doom("Allocation of t_collisions failed");
	collisions = *first;
	collisions->item.wall = NULL;
	collisions->item.last_portal = NULL;
	collisions->next = NULL;
	while (check_collision_in_sector(sector, seg, &collisions->item)
			&& collisions->item.wall->type != e_wall)
	{
		last_portal = collisions->item.wall;
		sector = get_next_sector_addr(sector, collisions->item.wall);
		if (!(collisions->next = (t_collisions *)malloc(sizeof(t_collisions))))
			error_doom("Allocation of t_collisions failed");
		collisions = collisions->next;
		collisions->item.last_portal = last_portal;
		collisions->item.wall = NULL;
		collisions->next = NULL;
	}
}