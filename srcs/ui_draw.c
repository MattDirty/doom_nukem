/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfatton <lfatton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 00:44:00 by lfatton           #+#    #+#             */
/*   Updated: 2019/04/11 00:44:07 by lfatton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <SDL.h>
#include "map.h"
#include "doom.h"
#include "ui.h"
#include "default.h"

void	ui_draw(SDL_Surface *surface, t_map *map, int fps, t_env *e)
{
	draw_crosshair(surface, &e->op, CROSSHAIR_COLOR);
	draw_fps(e->fonts->sixty20, surface, fps);
	draw_sun_or_moon(surface, map, &e->op);
	draw_health(e);
	draw_ammo(e, map->hud.bullet, e->p.weapon->ammo);
	draw_face(surface, &map->hud, &e->p, &e->op);
}
