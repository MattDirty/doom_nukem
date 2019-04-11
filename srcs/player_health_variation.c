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

void    game_over(SDL_Surface *surface, t_config *op)
{
    SDL_Surface *game_over;
    t_coords    location;

    game_over = write_text("fonts/horrendo.ttf", 120, "GAME OVER!", (SDL_Colour){255,0,0,255});
    location.x = op->half_w - game_over->w / 2;
    location.y = op->half_h - game_over->h / 2;
    draw_on_screen(surface, game_over, location, t_false);
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
        if (p->health <= 0)
            p->dead = t_true;
        p->hurt = t_true;
    }
    if (state[SDL_SCANCODE_K])
    {
        p->health += HEAL;
        if (p->health >= HEALTH_MAX)
            p->health = HEALTH_MAX;
        p->healed = t_true;
    }
    if (p->dead)
    {
        p->health = 0;
        p->hurt = t_false;
        p->healed = t_false;
    }

}
