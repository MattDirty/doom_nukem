/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoinfree.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfatton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/30 15:48:40 by lfatton           #+#    #+#             */
/*   Updated: 2018/06/13 18:50:37 by lfatton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strjoinfree(char const *s1, char const *s2, int opt)
{
	char	*str;

	str = ft_strjoin(s1, s2);
	if (s1 && (opt & 1))
		free((void*)s1);
	if (s2 && (opt & 2))
		free((void*)s2);
	return (str);
}
