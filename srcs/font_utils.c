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

t_font        load_fonts(void)
{
    t_font  font;

    if (!(font.game_over = TTF_OpenFont("fonts/horrendo.ttf", 40)))
        error_doom("error: couldn't load font: game_over");
    if (!(font.nightnday = TTF_OpenFont("fonts/sixty.ttf", 20)))
        error_doom("error: couldn't load font: nightnday");
    return (font);
};
