/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfatton <lfatton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 16:02:56 by lfatton           #+#    #+#             */
/*   Updated: 2019/03/18 16:03:13 by lfatton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <unistd.h>
#include <stdlib.h>

#include "utils.h"

double  get_distance_between_points(double x1, double y1, double x2, double y2)
{
    return (sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2)));
}

int			read_segment_from_file(int fd, t_segment **segment)
{
    int res;

    if (!(*segment = (t_segment*)malloc(sizeof(t_segment))))
        return (-1);

    res = read(fd, &((*segment)->x1), sizeof((*segment)->x1));
    res &= read(fd, &((*segment)->y1), sizeof((*segment)->y1));
    res &= read(fd, &((*segment)->x2), sizeof((*segment)->x2));
    res &= read(fd, &((*segment)->y2), sizeof((*segment)->y2));

    return (res);
}

int			write_segment_to_file(int fd, t_segment *segment)
{
    int res;

    res = write(fd, &(segment->x1), sizeof(segment->x1));
    res &= write(fd, &(segment->y1), sizeof(segment->y1));
    res &= write(fd, &(segment->x2), sizeof(segment->x2));
    res &= write(fd, &(segment->y2), sizeof(segment->y2));

    return (res);
}
