/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_elements.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfatton <lfatton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 00:34:37 by lfatton           #+#    #+#             */
/*   Updated: 2019/04/11 00:34:39 by lfatton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SDL.h"
#include "libft.h"
#include "default.h"
#include "utils.h"
#include "surface_manipulation.h"
#include "config.h"
#include "ui.h"

void        draw_crosshair(SDL_Surface *surface, t_config *op, Uint32 color)
{
    t_segment   segment;

    segment.x1 = op->half_w;
    segment.y1 = op->half_h - 30;
    segment.x2 = op->half_w;
    segment.y2 = op->half_h - 30 - 50;
    draw_segment(surface, segment, color);
    segment.x1 = op->half_w - 30;
    segment.y1 = op->half_h;
    segment.x2 = op->half_w - 30 - 50;
    segment.y2 = op->half_h;
    draw_segment(surface, segment, color);
    segment.x1 = op->half_w;
    segment.y1 = op->half_h + 30;
    segment.x2 = op->half_w;
    segment.y2 = op->half_h + 30 + 50;
    draw_segment(surface, segment, color);
    segment.x1 = op->half_w + 30;
    segment.y1 = op->half_h;
    segment.x2 = op->half_w + 30 + 50;
    segment.y2 = op->half_h;
    draw_segment(surface, segment, color);
    put_pixel_alpha(surface, op->half_w, op->half_h, color);
}

void        draw_fps(TTF_Font *font, SDL_Surface *surface, int fps)
{
    SDL_Surface *fps_text;
    t_coords    location;
    char        *charabia;

    location.x = 10;
    location.y = 10;
    charabia = ft_strjoinfree(ft_itoa(fps), " fps", 1);
    fps_text = write_text(font, charabia, (SDL_Colour){255,255,255,255});
    draw_on_screen(surface, fps_text, location, t_false);
    free(charabia);
    free(fps_text);
}

void        draw_health(t_env *e)
{
    SDL_Surface *health;
    t_coords    location;
    char        *charivari;

    location.x = e->op.half_w + 200;
    location.y = e->op.win_h - 45;
    charivari = ft_itoa((int)e->p.health);
    health = write_text(e->fonts->sixty40, charivari, (SDL_Colour){244, 182, 66, 255});
    draw_on_screen(e->doom.surface, health, location, t_false);
    if (e->map->hud.id > 2 || e->p.dead)
        e->map->hud.id = 0;
    location.x = e->op.half_w + 150;
    location.y = e->op.win_h - 50;
    draw_on_screen(e->doom.surface, e->map->hud.cross[e->map->hud.id], location, t_false);
    free(charivari);
    free(health);
}

void        draw_ammo(t_env *e, SDL_Surface *bullet, int ammo)
{
    SDL_Surface *ammo_nb;
    t_coords    location;
    char        *charlatan;

    charlatan = ft_itoa(ammo);
    location.x = e->op.half_w - 300;
    location.y = e->op.win_h - 45;
    if (ammo == -1)
    {
        location.y = e->op.win_h - 35;
        ammo_nb = write_text(e->fonts->sixty40, "8",
                             (SDL_Colour){0, 0, 0, 255});
        rotate_and_draw(e->doom.surface, ammo_nb, location, t_false);
    }
    else
    {
        ammo_nb = write_text(e->fonts->sixty40, charlatan,
                             (SDL_Colour){0, 0, 0, 255});
        draw_on_screen(e->doom.surface, ammo_nb, location, t_false);
    }
    location.x = e->op.half_w - 350;
    location.y = e->op.win_h - 52;
    draw_on_screen(e->doom.surface, bullet, location, t_false);
    free(charlatan);
    free(ammo_nb);
}
