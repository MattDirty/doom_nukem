/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfatton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 06:56:05 by lfatton           #+#    #+#             */
/*   Updated: 2019/04/19 06:56:08 by lfatton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "default.h"
#include "config.h"

t_config	load_default_config()
{
	t_config	config;

	config.win_w = WIN_W;
	config.win_h = WIN_H;
	config.half_w = HALF_W;
	config.half_h = HALF_H;
	config.ratio = RATIO;
	config.fullscreen = FULLSCREEN;
	config.fov = FOV;
	config.half_fov = HALF_FOV;
	config.fps_max = FPS_MAX;
	config.mouse_sensi = MOUSE_SENSI;
	config.tan_half_fov = TAN_HALF_FOV;
	config.ratio = RATIO;
	config.lights = ACTIVATE_LIGHTING;
	return (config);
}
