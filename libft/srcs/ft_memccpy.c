/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfatton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/23 17:34:25 by lfatton           #+#    #+#             */
/*   Updated: 2018/04/26 14:29:42 by lfatton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t			i;
	unsigned char	ccpy;
	unsigned char	*dstcpy;
	unsigned char	*srccpy;

	ccpy = (unsigned char)c;
	dstcpy = (unsigned char*)dst;
	srccpy = (unsigned char*)src;
	i = 0;
	while (i < n)
	{
		(dstcpy)[i] = (srccpy)[i];
		if (ccpy == (srccpy)[i])
			return (&dstcpy[i + 1]);
		i++;
	}
	return (NULL);
}
