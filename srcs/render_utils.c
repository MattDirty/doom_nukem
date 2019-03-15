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

void	put_pixel(SDL_Surface *s, int x, int y, t_color color)
{
	Uint32	*pix;
	Uint8	red;
	Uint8	green;
	Uint8	blue;

	if (x < 0 || y < 0)
		return;
	pix = (Uint32 *)s->pixels + (x + y * s->w);
	red = (*pix & s->format->Rmask) >> s->format->Rshift << s->format->Rloss;
	green = (*pix & s->format->Gmask) >> s->format->Gshift << s->format->Gloss;
	blue = (*pix & s->format->Bmask) >> s->format->Bshift << s->format->Bloss;
	color.red = (color.red * (color.alpha / 255.0)) + (red * ((255 - color.alpha) / 255));
	color.green = (color.green * (color.alpha / 255.0)) + (green * ((255 - color.alpha) / 255));
	color.blue = (color.blue * (color.alpha / 255.0)) + (blue * ((255 - color.alpha) / 255));
	color.alpha = 255;
	*pix = t_color_to_int(color);
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
