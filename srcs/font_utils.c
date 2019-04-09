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

void        load_fonts(void)
{
    TTF_Font    *game_over;
    TTF_Font    *nightnday;

    if (!(game_over = TTF_OpenFont("fonts/horrendo.ttf", 40)))
        error_doom("error: couldn't load font: game_over");
    if (!(nightnday = TTF_OpenFont("fonts/sixty.ttf", 20)))
        error_doom("error: couldn't load font: nightnday");
};
