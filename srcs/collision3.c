/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtorsell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/20 17:53:22 by mtorsell          #+#    #+#             */
/*   Updated: 2019/04/20 17:53:32 by mtorsell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "collision.h"
#include "default.h"

void			free_collisions(t_collisions *collisions)
{
	t_collisions	*buffer;

	while (collisions)
	{
		buffer = collisions->next;
		free(collisions);
		collisions = buffer;
	}
}
