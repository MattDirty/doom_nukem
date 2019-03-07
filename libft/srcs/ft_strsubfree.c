/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsubfree.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfatton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/01 00:27:22 by lfatton           #+#    #+#             */
/*   Updated: 2018/06/01 00:43:30 by lfatton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strsubfree(char const *s, unsigned int start, size_t len)
{
	char	*str;

	str = ft_strsub(s, start, len);
	free((void*)s);
	return (str);
}
