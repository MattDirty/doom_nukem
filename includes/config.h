/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfatton <lfatton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 05:37:47 by lfatton           #+#    #+#             */
/*   Updated: 2019/04/12 05:37:55 by lfatton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIG_H
# define CONFIG_H

# include "e_bool.h"
# include "SDL.h"

typedef struct  s_config
{
    Uint32      win_w;
    Uint32      win_h;
    double      half_w;
    double      half_h;
    double      ratio;

    enum e_bool fullscreen;

    double      fov;
    double      half_fov;
    double      tan_half_fov;

    int         fps_max;

    double      mouse_sensi;

    enum e_bool	lights;
}               t_config;

t_config    load_config();

#endif
