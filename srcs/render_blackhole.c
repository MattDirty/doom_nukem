/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_blackhole.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfatton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/20 11:09:53 by lfatton           #+#    #+#             */
/*   Updated: 2019/04/20 11:09:54 by lfatton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render_blackhole.h"

void	put_pixel_blackhole(t_env *e, int x, int y, Uint32 color)
{
	Uint32	*pix;
	Uint32	alpha;
	Uint32	rb;
	Uint32	g;

	alpha = (color & 0xff000000) >> 24;
	if (alpha == 0)
		return ;
	if (e->blackhole_buffer[x + y * e->doom.surface->w])
	{
		pix = e->doom.surface->pixels;
		pix[x + y * e->doom.surface->w] = 0xff000000;
		return ;
	}
	pix = (Uint32 *)e->doom.surface->pixels + x + y * e->doom.surface->w;
	rb = ((0x100 - alpha) * (*pix & 0xff00ff)) >> 8
		| (alpha * (color & 0xff00ff)) >> 8;
	g = ((0x100 - alpha) * (*pix & 0x00ff00)) >> 8
		| (alpha * (color & 0x00ff00)) >> 8;
	*pix = 0xff000000 | (rb & 0xff00ff) | (g & 0x00ff00);
}
