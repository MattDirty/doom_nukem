/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfatton <lfatton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 00:12:03 by lfatton           #+#    #+#             */
/*   Updated: 2019/04/11 00:12:13 by lfatton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "player.h"
#include "default.h"
#include "config.h"
#include "ui.h"

t_player init_player(t_config *op, t_sector *starting_sector)
{
    t_player p;

    p.vision_height = op->half_h;
    p.heading = EAST;
    p.current_sector = starting_sector;
    p.pos.y = 2;
    p.pos.x = 3;
    p.speed.x = 0;
    p.speed.y = 0;
    p.speed_factor = 1;
    p.jump.ready = t_true;
    p.jump.height = 0;
    p.jump.gravity = 0.1;
    p.jump.duration = 400;
    p.jump.time = 0;
    p.dead = t_false;
    p.health = 100;
    p.healed = t_false;
    p.hurt = t_false;
    return (p);
}

void	clamp_player_values(t_player *p, t_config op)
{
    while (p->heading >= CIRCLE)
        p->heading -= CIRCLE;
    while (p->heading < 0)
        p->heading += CIRCLE;
    p->vision_height > op.win_h ? p->vision_height = op.win_h : 0;
    p->vision_height < 0 ? p->vision_height = 0 : p->vision_height;
    if (p->health <= 0)
        p->dead = t_true;
    if (p->dead)
    {
        p->health = 0;
        p->hurt = t_false;
        p->healed = t_false;
    }
}

void    draw_face(SDL_Surface *surface, t_hud *hud, t_player *p, t_config *op)
{
    t_coords    location;

    location.x = op->half_w + 275;
    location.y = op->win_h - 75;
    if (location.x >= op->win_w)
        location.x = op->half_w;
    if (location.y < 0)
        location.y = 0;
    if (!p->weapon->main_ready)
        draw_on_screen(surface, hud->badass_face, location, t_true);
    else if (p->healed)
        draw_on_screen(surface, hud->sehr_happy_face, location, t_true);
    else if (p->hurt)
        draw_on_screen(surface, hud->hurt_face, location, t_true);
    else if (p->health > 75)
        draw_on_screen(surface, hud->happy_face, location, t_true);
    else if (p->health <= 75 && p->health >= 50)
        draw_on_screen(surface, hud->meh_face, location, t_true);
    else if (p->health < 50 && p->health >= 1)
        draw_on_screen(surface, hud->sad_face, location, t_true);
    else if (p->dead)
        draw_on_screen(surface, hud->dead_face, location, t_true);
}
