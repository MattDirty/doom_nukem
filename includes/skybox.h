/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skybox.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfatton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/29 23:13:18 by lfatton           #+#    #+#             */
/*   Updated: 2019/03/29 23:13:20 by lfatton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SKYBOX_H
# define SKYBOX_H

#include "doom.h"
#include "timer_handler.h"
#include "SDL.h"

enum e_bool day_to_night(double ms_since_update, t_params daytime);
void        skybox(t_env *e, Uint32 renderer_x);

#endif
