/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_radtodeg.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfatton <lfatton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 16:06:55 by lfatton           #+#    #+#             */
/*   Updated: 2019/03/08 16:38:04 by lfatton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

double	ft_radtodeg(double value)
{
	return (value * 180 / M_PI);
}
