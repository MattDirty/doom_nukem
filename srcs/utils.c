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

#include "doom.h"

double  get_distance_between_points(double x1, double y1, double x2, double y2)
{
    return(sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2)));
}
