/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badhont <badhont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 00:56:09 by lfatton           #+#    #+#             */
/*   Updated: 2019/04/10 19:20:04 by badhont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "default.h"
#include <SDL.h>
#include "e_bool.h"
#include "doom.h"

Uint32	get_pixel_for_runtime_generated(SDL_Surface *s, int x, int y,
			enum e_bool force_alpha)
{
	Uint32	*pix;
	Uint8	channel[4];
	Uint32	color;

	pix = (Uint32 *)s->pixels;
	color = pix[x + y * s->w];
	if (force_alpha)
		channel[0] = 255;
	else
		channel[0] = (color & s->format->Amask) >> s->format->Ashift
			<< s->format->Aloss;
	channel[1] = (color & s->format->Rmask) >> s->format->Rshift
		<< s->format->Rloss;
	channel[2] = (color & s->format->Gmask) >> s->format->Gshift
		<< s->format->Gloss;
	channel[3] = (color & s->format->Bmask) >> s->format->Bshift
		<< s->format->Bloss;
	color = (channel[0] << 24) + (channel[1] << 16) + (channel[2] << 8)
		+ (channel[3]);
	return (color);
}

void	put_pixel_alpha_for_runtime_generated(SDL_Surface *s, int x, int y,
			Uint32 color)
{
	Uint32	*pix;
	double	alpha;
	Uint8	pred;
	Uint8	pgreen;
	Uint8	pblue;

	alpha = ((color & MASK_ALPHA) >> 24) / 255.0;
	if (x < 0 || y < 0 || alpha == 0)
		return ;
	if (x >= s->w || y >= s->h)
		return ;
	pix = (Uint32 *)s->pixels + (x + y * s->w);
	pred = (*pix & s->format->Rmask) >> s->format->Rshift << s->format->Rloss;
	pgreen = (*pix & s->format->Gmask) >> s->format->Gshift << s->format->Gloss;
	pblue = (*pix & s->format->Bmask) >> s->format->Bshift << s->format->Bloss;
	*pix = (255 << 24) + ((int)(((color & MASK_RED) >> 16) * alpha + (pred
				* (1 - alpha))) << 16)
				+ ((int)(((color & MASK_GREEN) >> 8) * alpha
				+ (pgreen * (1 - alpha))) << 8)
				+ (color & MASK_BLUE) * alpha + pblue * (1 - alpha);
}

Uint32	get_pixel(SDL_Surface *s, int x, int y, enum e_bool force_alpha)
{
	Uint8	*pix;
	Uint32	color;

	pix = s->pixels + (x + y * s->w) * 4;
	color = *pix << 24 | *(pix + 3) << 16 | *(pix + 2) << 8 | *(pix + 1);
	if (force_alpha)
		color |= 0xff000000;
	return (color);
}

void	put_pixel(SDL_Surface *s, int x, int y, Uint32 color)
{
	Uint32	*pix;

	pix = s->pixels;
	pix[x + y * s->w] = color;
}

void	put_pixel_alpha(SDL_Surface *s, int x, int y, Uint32 color)
{
	Uint32	*pix;
	Uint32	alpha;
	Uint32	rb;
	Uint32	g;

	alpha = (color & 0xff000000) >> 24;
	if (alpha == 0)
		return ;
	if (alpha == 0xff)
	{
		pix = s->pixels;
		pix[x + y * s->w] = color;
		return ;
	}
	pix = (Uint32 *)s->pixels + x + y * s->w;
	rb = ((0x100 - alpha) * (*pix & 0xff00ff)) >> 8 | (alpha
		* (color & 0xff00ff)) >> 8;
	g = ((0x100 - alpha) * (*pix & 0x00ff00)) >> 8 | (alpha
		* (color & 0x00ff00)) >> 8;
	*pix = 0xff000000 | (rb & 0xff00ff) | (g & 0x00ff00);
}
