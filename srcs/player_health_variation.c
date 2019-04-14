/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_health_variation.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfatton <lfatton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 00:10:58 by lfatton           #+#    #+#             */
/*   Updated: 2019/04/11 00:11:00 by lfatton          ###   ########.fr       */
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
    draw_on_screen(surface, game_over, pos, t_false);
    free(game_over);
}

enum e_bool toggle_player_health(double ms_since_update, t_params pointer)
{
    t_player    *p;
    (void)ms_since_update;

    p = (t_player*)pointer;
    p->hurt = t_false;
    p->healed = t_false;
    return (t_true);
}

void    hurt_or_heal(t_player *p, const Uint8 *state)
{
    if (state[SDL_SCANCODE_J])
    {
        p->health -= DAMAGE;
        p->hurt = t_true;
    }
    if (state[SDL_SCANCODE_K])
    {
        p->health += HEAL;
        if (p->health >= HEALTH_MAX)
            p->health = HEALTH_MAX;
        p->healed = t_true;
    }

}
