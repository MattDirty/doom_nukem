/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfatton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/07 15:43:31 by lfatton           #+#    #+#             */
/*   Updated: 2018/04/26 01:21:06 by lfatton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *dst, const char *src)
{
	size_t	i;
	size_t	j;
	size_t	len;
	size_t	count;

	j = 0;
	if (!(len = ft_strlen(src)))
		return (char*)(dst);
	while (dst[j])
	{
		i = 0;
		count = 0;
		while (src[i])
		{
			if (src[i] == dst[count + j])
				count++;
			if (count == len)
				return ((char*)&dst[(j + count) - (len)]);
			i++;
		}
		j++;
	}
	return (NULL);
}
