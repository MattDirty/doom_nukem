/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfatton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/20 18:30:34 by lfatton           #+#    #+#             */
/*   Updated: 2018/04/26 15:12:05 by lfatton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_itoa(int n)
{
	size_t			len;
	unsigned int	ncpy;
	char			*nbinstr;

	ncpy = ft_abs(n);
	len = ft_nbrlen(n, 10);
	if (!(nbinstr = ft_strnew(len)))
		return (NULL);
	if (n < 0)
		nbinstr[0] = '-';
	else if (n == 0)
		nbinstr[0] = '0';
	nbinstr[len] = '\0';
	while (ncpy > 0)
	{
		nbinstr[len - 1] = (ncpy % 10) + '0';
		ncpy /= 10;
		len--;
	}
	return (nbinstr);
}
