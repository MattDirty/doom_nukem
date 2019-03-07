/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfatton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/20 17:36:41 by lfatton           #+#    #+#             */
/*   Updated: 2018/04/26 13:58:33 by lfatton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char		**ft_strsplit(char const *s, char c)
{
	int		i;
	int		j;
	int		k;
	char	**spl;

	i = 0;
	j = 0;
	if (!s || !(spl = (char**)malloc(sizeof(char*) * ft_count_words(s, c) + 1)))
		return (NULL);
	while (s[i] == c)
		i++;
	while (s[i])
	{
		k = 0;
		if (!(spl[j] = ft_strnew(ft_strcleni(s, i, c))))
			return (NULL);
		while (s[i] && s[i] != c)
			spl[j][k++] = s[i++];
		while (s[i] == c)
			i++;
		spl[j++][k] = '\0';
	}
	spl[j] = NULL;
	return (spl);
}
