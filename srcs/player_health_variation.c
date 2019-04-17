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

#include "e_bool.h"
#include "player.h"

enum e_bool toggle_player_health(double ms_since_update, t_params pointer)
{
    t_player    *p;
    (void)ms_since_update;

    p = (t_player*)pointer;
    p->hurt = e_false;
    p->healed = e_false;
    return (e_true);
}
