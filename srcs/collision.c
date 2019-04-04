#include "collision.h"
#include "default.h"

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

Uint32  check_collision(t_sector *sector, t_segment *seg, t_collision **collision)
{
	t_wall	*last_portal;
	Uint32  i;

	last_portal = NULL;
	i = 0;
	if (!(*collision = (t_collision *)malloc(sizeof(t_collision))))
		error_doom("Can't malloc collision");
	while (check_collision_in_sector(sector, seg, &collision[0][i]))
	{
		i++;
		update_collisions_list(collision, i);
		if (collision[0][i - 1].wall->type != wtWall)
		{
			last_portal = collision[0][i - 1].wall;
			sector = get_next_sector_addr(sector, collision[0][i - 1].wall);
		}
		else
			break;
	}
	return (i);
}