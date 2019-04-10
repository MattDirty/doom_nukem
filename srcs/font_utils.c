/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   font_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfatton <lfatton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 11:16:12 by lfatton           #+#    #+#             */
/*   Updated: 2019/04/09 11:16:14 by lfatton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SDL_ttf.h"
#include "doom.h"

SDL_Surface *write_text(char *font_path, int font_size, char *str, SDL_Colour color)
{
    SDL_Surface *text;
    TTF_Font    *font;

    if (!(font = TTF_OpenFont(font_path, font_size)))
        error_doom("error: couldn't load font");
    if (!(text = TTF_RenderText_Blended(font, str, color)))
        error_doom("error: cannot write on screen");
    TTF_CloseFont(font);
    return (text);
}
