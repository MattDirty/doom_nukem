/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapon_draw.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtorsell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/20 00:44:11 by mtorsell          #+#    #+#             */
/*   Updated: 2019/04/20 00:44:16 by mtorsell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "surface_manipulation.h"
#include "animation.h"
#include "config.h"

void	draw_weapon(
			SDL_Surface *surface,
			SDL_Surface *weapon, t_animation *animation,
			t_config *op)
{
	int x;
	int y;
	int x1;
	int y1;

	y = -1;
	while (++y < weapon->h)
	{
		x = -1;
		y1 = (op->win_h - weapon->h) + y + animation->y_offset;
		if (y1 < 0 || y1 > surface->h)
			continue;
		while (++x < weapon->w)
		{
			x1 = (op->half_w - (weapon->w / 2)) + x + animation->x_offset;
			if (x1 < 0 || x1 > surface->w)
				continue;
			put_pixel_alpha(surface, x1, y1, get_pixel(weapon, x, y, e_false));
		}
	}
}
