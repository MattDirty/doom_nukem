/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_health_variation.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfatton <lfatton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 00:10:58 by lfatton           #+#    #+#             */
/*   Updated: 2019/04/16 01:48:59 by mtorsell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SDL.h"
#include "config.h"
#include "default.h"
#include "utils.h"
#include "ui.h"

void    game_over(TTF_Font *font, SDL_Surface *surface, t_config *op)
{
    SDL_Surface *game_over;
    t_i_coords  pos;

    game_over = write_text(font, "GAME OVER!", (SDL_Colour){255,0,0,255});
    pos.x = op->half_w - game_over->w / 2;
    pos.y = op->half_h - game_over->h / 2;
    draw_on_screen(surface, game_over, pos, e_false);
    SDL_FreeSurface(game_over);
}

enum e_bool toggle_player_health(double ms_since_update, t_params pointer)
{
    t_player    *p;
    (void)ms_since_update;

    p = (t_player*)pointer;
    p->hurt = e_false;
    p->healed = e_false;
    return (e_true);
}
