/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfatton <lfatton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 00:56:09 by lfatton           #+#    #+#             */
/*   Updated: 2019/03/08 13:39:29 by lfatton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

Uint32	get_pixel(SDL_Surface *s, int x, int y, enum e_bool force_alpha)
{
	Uint32	*pix;
	Uint8	channel[4];
	Uint32	color;

	pix = (Uint32*)s->pixels;
	color = pix[x + y * s->w];
	if (force_alpha)
		channel[0] = 255;
	else
		channel[0] = (color & s->format->Amask) >> s->format->Ashift << s->format->Aloss;
	channel[1] = (color & s->format->Rmask) >> s->format->Rshift << s->format->Rloss;
	channel[2] = (color & s->format->Gmask) >> s->format->Gshift << s->format->Gloss;
	channel[3] = (color & s->format->Bmask) >> s->format->Bshift << s->format->Bloss;
	color = (channel[0] << 24) + (channel[1] << 16) + (channel[2] << 8) + (channel[3]);
	return (color);
}

void	put_pixel(SDL_Surface *s, int x, int y, Uint32 color)
{
	Uint8	*pix;
	Uint32	i;
	Uint8	red;
	Uint8	green;
	Uint8	blue;

	if (x < 0 || y < 0)
		return;
	i = (x + y * s->w) * 4;
	pix = (Uint8 *)s->pixels;
	red = (color & s->format->Rmask) >> s->format->Rshift << s->format->Rloss;
	green = (color & s->format->Gmask) >> s->format->Gshift << s->format->Gloss;
	blue = (color & s->format->Bmask) >> s->format->Bshift << s->format->Bloss;
	color = (color & s->format->Amask) >> s->format->Ashift << s->format->Aloss;
	if (color != 255 && pix[i] != 0)
	{
		red = (red * (Uint8)color / 255.0) + (pix[i + 1] * (255 - (Uint8)color));
		green = (green * (Uint8)color / 255.0) + (pix[i + 2] * (255 - (Uint8)color));
		blue = (blue * (Uint8)color / 255.0) + (pix[i + 3] * (255 - (Uint8)color));
	}
	pix[i + s->format->Ashift / 8] = 255;
	pix[i + s->format->Rshift / 8] = red;
	pix[i + s->format->Gshift / 8] = green;
	pix[i + s->format->Bshift / 8] = blue;
}

void	print_surface(SDL_Renderer *renderer, SDL_Surface *surface)
{
	SDL_Texture *texture;

	if (!(texture = SDL_CreateTextureFromSurface(renderer, surface)))
		error_doom("error: cannot create texture");
	SDL_RenderCopy(renderer, texture, NULL, NULL);
	SDL_RenderPresent(renderer);
	SDL_DestroyTexture(texture);
}
