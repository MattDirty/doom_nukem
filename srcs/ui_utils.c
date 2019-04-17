/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfatton <lfatton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 00:34:49 by lfatton           #+#    #+#             */
/*   Updated: 2019/04/11 00:34:51 by lfatton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SDL_ttf.h"
#include "doom.h"

enum e_bool cross_index(double ms_since_update, t_params i)
{
    (void)ms_since_update;
    (*(int*)i)++;
    return (e_true);
}

SDL_Surface *write_text(TTF_Font *font, char *str, SDL_Colour color)
{
    SDL_Surface *text;

    if (!(text = TTF_RenderText_Blended(font, str, color)))
        error_doom("error: cannot write on screen");
    return (text);
}
