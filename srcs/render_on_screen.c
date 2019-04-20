/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_on_screen.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfatton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/20 10:48:20 by lfatton           #+#    #+#             */
/*   Updated: 2019/04/20 10:48:21 by lfatton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <SDL.h>
#include "default.h"
#include "e_bool.h"
#include "doom.h"
#include "surface_manipulation.h"

void	rotate_and_draw(SDL_Surface *surface, SDL_Surface *text, t_i_coords pos,
			enum e_bool force_alpha)
{
	int	x;
	int	y;

	x = 0;
	while (x < text->w)
	{
		y = text->h - 1;
		while (y >= 0)
		{
			if (pos.x + y < surface->w && pos.y + x < surface->h
				&& pos.x + y >= 0 && pos.y + x >= 0
				&& x < text->w && y < text->h
				&& x >= 0 && y >= 0)
				put_pixel_alpha(surface, pos.x + y, pos.y + x,
					get_pixel_for_runtime_generated(text, x, y, force_alpha));
			y--;
		}
		x++;
	}
}

void	draw_on_screen(SDL_Surface *surface, SDL_Surface *text, t_i_coords pos,
			enum e_bool force_alpha)
{
	int x;
	int y;

	y = 0;
	while (y < text->h)
	{
		x = 0;
		while (x < text->w)
		{
			if (pos.x + x < surface->w && pos.y + y < surface->h
				&& pos.x + x >= 0 && pos.y + y >= 0
				&& x < text->w && y < text->h
				&& x >= 0 && y >= 0)
				put_pixel_alpha_for_runtime_generated(surface, pos.x + x,
					pos.y + y, get_pixel_for_runtime_generated(
						text, x, y, force_alpha));
			x++;
		}
		y++;
	}
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
