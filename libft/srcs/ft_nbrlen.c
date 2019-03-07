/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nbrlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfatton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/25 20:44:36 by lfatton           #+#    #+#             */
/*   Updated: 2018/04/26 15:10:47 by lfatton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_nbrlen(int nb, int base)
{
	size_t			res;
	unsigned int	ncpy;

	res = 0;
	ncpy = ft_abs(nb);
	if (base == 10 && nb < 0)
		res++;
	if (nb == 0)
		return (1);
	while (ncpy > 0)
	{
		ncpy /= base;
		res++;
	}
	return (res);
}
