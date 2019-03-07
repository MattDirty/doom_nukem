/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfatton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/07 20:38:06 by lfatton           #+#    #+#             */
/*   Updated: 2018/04/25 23:51:29 by lfatton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *dst, const char *src, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	length;
	size_t	count;

	j = 0;
	if (!(length = ft_strlen(src)))
		return (char*)(dst);
	while (dst[j])
	{
		i = 0;
		count = 0;
		while (src[i])
		{
			if (src[i] == dst[count + j])
				count++;
			if (count == length && ((j + count)) <= len)
				return ((char*)&dst[(j + count) - (length)]);
			i++;
		}
		j++;
	}
	return (NULL);
}
