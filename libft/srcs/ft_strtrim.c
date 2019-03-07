/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfatton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/23 16:07:31 by lfatton           #+#    #+#             */
/*   Updated: 2018/04/26 13:42:22 by lfatton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	size_t	i;
	size_t	end;
	size_t	len;

	if (s)
	{
		i = 0;
		end = ft_strlen(s) - 1;
		while (s[i] && (s[i] == '\n' || ft_isblank(s[i])))
			i++;
		while (s[end] && (s[end] == '\n' || ft_isblank(s[end])))
			end--;
		if (i == ft_strlen(s))
			return (ft_strdup(""));
		len = end + 1 - i;
		return (ft_strsub(s, i, len));
	}
	return (NULL);
}
