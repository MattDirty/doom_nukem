/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sectors2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtorsell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/20 03:53:38 by mtorsell          #+#    #+#             */
/*   Updated: 2019/04/20 03:53:40 by mtorsell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "textures.h"
#include "serialisation.h"
#include "sectors.h"
#include "objects.h"
#include "doom.h"
#include "enemies.h"
#include "utils.h"

void		set_default_sector(t_sector **sector)
{
	if (!(*sector = (t_sector*)malloc(sizeof(t_sector))))
		error_doom("Couldn't allocate sector");
	if (!((*sector)->walls = (t_walls *)malloc(sizeof(t_walls))))
		error_doom("couldn't allocate walls");
	(*sector)->walls->count = 0;
	(*sector)->floor = NULL;
	(*sector)->ceil = NULL;
	(*sector)->light = 0;
	if (!((*sector)->objects = (t_objects *)malloc(sizeof(t_objects))))
		error_doom("Couldn't allocate objects");
	(*sector)->objects->items = NULL;
	(*sector)->objects->count = 0;
	(*sector)->enemies = NULL;
	(*sector)->pickables = NULL;
}

t_sector	*create_new_sector(t_sectors *sectors)
{
	t_sector	**items;
	int			count;
	int			i;

	count = sectors->count + 1;
	if (!(items = (t_sector**)malloc(sizeof(t_sector*) * count)))
		error_doom("Couldn't allocate new sector");
	i = 0;
	while (i < sectors->count)
	{
		items[i] = sectors->items[i];
		i++;
	}
	free(sectors->items);
	sectors->items = items;
	sectors->count++;
	set_default_sector(&items[i]);
	return (items[i]);
}

void		add_wall_to_sector(t_sector *sector, t_wall *wall)
{
	int		count;
	t_wall	**items;
	int		i;

	count = sector->walls->count + 1;
	if (!(items = (t_wall **)malloc(sizeof(t_wall *) * count)))
		error_doom("Couldn't add a wall to sector(malloc)");
	i = 0;
	while (i < sector->walls->count)
	{
		*(items + i) = *(sector->walls->items + i);
		i++;
	}
	if (sector->walls->count > 0)
		free(sector->walls->items);
	*(items + i) = wall;
	sector->walls->items = items;
	sector->walls->count = count;
}

enum e_bool	walls_intersection_in_sector(t_sector *sector)
{
	int			i;
	int			j;
	t_coords	inter;
	t_segment	s1;
	t_segment	s2;

	i = 0;
	while (i < sector->walls->count)
	{
		j = i;
		s1 = sector->walls->items[i]->segment;
		while (++j < sector->walls->count)
		{
			s2 = sector->walls->items[j]->segment;
			if (segments_share_node(&s1, &s2))
				continue;
			if (segments_intersect(&s1, &s2, &inter))
				return (e_true);
		}
		i++;
	}
	return (e_false);
}
