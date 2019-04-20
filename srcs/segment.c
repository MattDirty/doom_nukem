/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   segment.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtorsell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/20 03:48:18 by mtorsell          #+#    #+#             */
/*   Updated: 2019/04/20 03:48:19 by mtorsell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "doom.h"
#include <math.h>
#include <unistd.h>

double		get_segment_length(t_segment *s)
{
	double length;

	length = sqrt((s->x1 - s->x2) * (s->x1 - s->x2)
			+ (s->y1 - s->y2) * (s->y1 - s->y2));
	return (length);
}

void		change_segment_length(t_segment *segment, double length)
{
	double origin_length;
	double delta_x;
	double delta_y;

	delta_x = segment->x1 - segment->x2;
	delta_y = segment->y1 - segment->y2;
	origin_length = sqrt(delta_x * delta_x + delta_y * delta_y);
	length -= origin_length;
	segment->x2 = segment->x2
		+ (segment->x2 - segment->x1) / origin_length * length;
	segment->y2 = segment->y2
		+ (segment->y2 - segment->y1) / origin_length * length;
}

t_segment	create_segment(double x1, double y1, double x2, double y2)
{
	t_segment a;

	a.x1 = x1;
	a.x2 = x2;
	a.y1 = y1;
	a.y2 = y2;
	return (a);
}

void		read_segment_from_file(int fd, t_segment *segment)
{
	if (read(fd, &(segment->x1), sizeof(segment->x1)) <= 0)
		error_doom("couldn't read segment x1");
	if (read(fd, &(segment->y1), sizeof(segment->y1)) <= 0)
		error_doom("couldn't read segment y1");
	if (read(fd, &(segment->x2), sizeof(segment->x2)) <= 0)
		error_doom("couldn't read segment x2");
	if (read(fd, &(segment->y2), sizeof(segment->y2)) <= 0)
		error_doom("couldn't read segment y2");
}

void		write_segment_to_file(int fd, t_segment *segment)
{
	if (write(fd, &(segment->x1), sizeof(segment->x1)) <= 0)
		error_doom("couldn't write segment x1");
	if (write(fd, &(segment->y1), sizeof(segment->y1)) <= 0)
		error_doom("couldn't write segment y1");
	if (write(fd, &(segment->x2), sizeof(segment->x2)) <= 0)
		error_doom("couldn't write segment x2");
	if (write(fd, &(segment->y2), sizeof(segment->y2)) <= 0)
		error_doom("couldn't write segment y2");
}
