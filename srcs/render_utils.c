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
#include "SDL.h"
#include "e_bool.h"
#include "doom.h"

Uint32  get_pixel(SDL_Surface *s, int x, int y, enum e_bool force_alpha)
{
    Uint8 *pix;
    Uint8 channel[4];
    Uint32 color;

    pix = s->pixels + (x + y * s->w) * s->format->BytesPerPixel;
    if (force_alpha)
        channel[0] = 255;
    else
        channel[0] = *pix;
    channel[1] = *(pix + 3);
    channel[2] = *(pix + 2);
    channel[3] = *(pix + 1);
    color = (channel[0] << 24) + (channel[1] << 16) + (channel[2] << 8) + (channel[3]);
    return (color);
}


void    put_pixel(SDL_Surface *s, int x, int y, Uint32 color)
{
    Uint32 *pix;

    pix = s->pixels;
    pix[x + y * s->w] = color;
}

void    put_pixel_alpha(SDL_Surface *s, int x, int y, Uint32 color)
{
    Uint32 *pix;
    Uint8 alpha;
    Uint32 pix_mask;
    Uint32 color_mask;

    alpha = (color & (0xff000000)) >> 24;
    if (alpha == 0)
        return;
    color_mask = (255 << 24) | (alpha << 16) | (alpha << 8) | alpha;
    pix_mask = (255 << 24) + ~color_mask;
    pix = (Uint32*)s->pixels + (x + y * s->w);
    *pix = (color & color_mask) + (*pix & pix_mask);
}

void        rotate_and_draw(SDL_Surface *surface, SDL_Surface *text, t_i_coords pos, enum e_bool force_alpha)
{
    int x;
    int y;

    x = 0;
    while (x < text->w)
    {
        y = text->h - 1;
        while (y >= 0)
        {
            put_pixel_alpha(surface, pos.x + y, pos.y + x,
                            get_pixel(text, x, y, force_alpha));
            y--;
        }
        x++;
    }

}

void        draw_on_screen(SDL_Surface *surface, SDL_Surface *text, t_i_coords pos, enum e_bool force_alpha)
{
    int x;
    int y;

    y = 0;
    while (y < text->h)
    {
        x = 0;
        while (x < text->w)
        {
            put_pixel_alpha(surface, pos.x + x, pos.y + y,
                            get_pixel(text, x, y, force_alpha));
            x++;
        }
        y++;
    }
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
