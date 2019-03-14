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

Uint32	get_pixel(SDL_Surface *s, int x, int y)
{
	Uint32	*pix;

	pix = (Uint32*)s->pixels;
	return (pix[x + y * s->w]);
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
