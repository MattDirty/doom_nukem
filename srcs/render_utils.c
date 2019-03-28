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

#include "default.h"
#include "SDL.h"
#include "e_bool.h"
#include "doom.h"

Uint32  get_pixel(SDL_Surface *s, int x, int y, enum e_bool force_alpha)
{
    Uint32 *pix;
    Uint8 channel[4];
    Uint32 color;

    pix = (Uint32 *) s->pixels;
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


void    put_pixel(SDL_Surface *s, int x, int y, Uint32 color)
{
    Uint32 *pix;

    if (x < 0 || y < 0)
        return;
    if (x >= s->w || y >= s->h)
        return;
    pix = (Uint32 *) s->pixels;
    pix[(Uint64)(x + y * s->w)] = color;
}

void    put_pixel_alpha(SDL_Surface *s, int x, int y, Uint32 color)
{
    Uint32 *pix;
    double alpha;
    Uint8 pRed;
    Uint8 pGreen;
    Uint8 pBlue;

    alpha = ((color & MASK_ALPHA) >> 24) / 255.0;
    if (x < 0 || y < 0 || alpha == 0)
        return;
    if (x >= s->w || y >= s->h)
        return;
    pix = (Uint32 *) s->pixels + (x + y * s->w);
    pRed = (*pix & s->format->Rmask) >> s->format->Rshift << s->format->Rloss;
    pGreen = (*pix & s->format->Gmask) >> s->format->Gshift << s->format->Gloss;
    pBlue = (*pix & s->format->Bmask) >> s->format->Bshift << s->format->Bloss;
    *pix = (255 << 24)
       + ((int) (((color & MASK_RED) >> 16) * alpha
       + (pRed * (1 - alpha))) << 16)
       + ((int) (((color & MASK_GREEN) >> 8) * alpha
       + (pGreen * (1 - alpha))) << 8)
       + (color & MASK_BLUE) * alpha + pBlue * (1 - alpha);
}

void    print_surface(SDL_Renderer *renderer, SDL_Surface *surface)
{
    SDL_Texture *texture;

    if (!(texture = SDL_CreateTextureFromSurface(renderer, surface)))
        error_doom("error: cannot create texture");
    SDL_RenderCopy(renderer, texture, NULL, NULL);
    SDL_RenderPresent(renderer);
    SDL_DestroyTexture(texture);
}
