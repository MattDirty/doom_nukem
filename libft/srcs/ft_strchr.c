/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfatton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/18 23:31:29 by lfatton           #+#    #+#             */
/*   Updated: 2018/06/13 18:45:51 by lfatton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	if (s)
	{
		if (c == '\0')
			return ((char*)s + ft_strlen(s));
		while (s[i])
		{
			if (s[i] == c)
				return ((char*)s + i);
			i++;
		}
	}
	return (NULL);
}
