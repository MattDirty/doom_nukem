/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfatton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/25 14:16:00 by lfatton           #+#    #+#             */
/*   Updated: 2018/04/25 14:41:24 by lfatton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	*ft_memdup(const void *mem, size_t n)
{
	void	*memmall;

	if (!(memmall = (void*)malloc(n)))
		return (NULL);
	return (ft_memcpy(memmall, mem, n));
}
