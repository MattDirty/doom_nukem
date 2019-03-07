/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcleni.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfatton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/26 00:05:15 by lfatton           #+#    #+#             */
/*   Updated: 2018/05/07 15:55:48 by lfatton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strcleni(const char *s, int start, char c)
{
	int	i;

	i = 0;
	if (s)
	{
		while (s[start + i] && s[start + i] != c)
			i++;
		return (i);
	}
	return (0);
}
