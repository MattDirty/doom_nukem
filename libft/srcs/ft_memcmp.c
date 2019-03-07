/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfatton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/20 20:35:05 by lfatton           #+#    #+#             */
/*   Updated: 2018/04/26 11:48:00 by lfatton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*s1cpy;
	unsigned char	*s2cpy;

	i = 0;
	s1cpy = (unsigned char*)s1;
	s2cpy = (unsigned char*)s2;
	if (n == 0)
		return (0);
	while (i < n - 1 && s1cpy[i] == s2cpy[i])
		i++;
	return (s1cpy[i] - s2cpy[i]);
}
