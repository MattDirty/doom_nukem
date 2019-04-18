/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_endings.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfatton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 23:42:17 by lfatton           #+#    #+#             */
/*   Updated: 2019/04/17 23:43:01 by lfatton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <SDL.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include "config.h"
#include "utils.h"
#include "ui.h"
#include "doom.h"

void    game_over(t_env *e, TTF_Font *font, SDL_Surface *surface, t_config *op)
{
    SDL_Surface *game_over;
    t_i_coords  pos;

    Mix_PlayChannel(-1, e->sounds->mwiiicrkk, 0);
    game_over = write_text(font, "GAME OVER!", (SDL_Colour){255,0,0,255});
    pos.x = op->half_w - game_over->w / 2;
    pos.y = op->half_h - game_over->h / 2;
    draw_on_screen(surface, game_over, pos, e_false);
    SDL_FreeSurface(game_over);
}

void    game_victory(TTF_Font *font, SDL_Surface *surface, t_config *op)
{
    SDL_Surface *victory;
    t_i_coords  pos;

    victory = write_text(font, "VICTORY!", (SDL_Colour){0,255,0,255});
    pos.x = op->half_w - victory->w / 2;
    pos.y = op->half_h - victory->h / 2;
    draw_on_screen(surface, victory, pos, e_false);
    SDL_FreeSurface(victory);
}
