/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfatton <lfatton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 05:50:12 by lfatton           #+#    #+#             */
/*   Updated: 2019/04/12 05:50:25 by lfatton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_H
# define PLAYER_H

# include "weapon.h"
# include "utils.h"
# include "map.h"
# include "SDL.h"
# include "config.h"

typedef struct          s_jump
{
    double              height;
    double              gravity;
    enum e_bool         ready;
    double              duration;
    double              time;
}                       t_jump;

typedef struct			s_player
{
	t_sector	*current_sector;
    t_coords	pos;
    double		heading;
    double		vision_height;
    double		speed_factor;
    t_vector    speed;
    t_weapons   weapons;
    t_jump      jump;
    enum e_bool dead;
    int         health;
    enum e_bool healed;
    enum e_bool hurt;
}						t_player;

t_player    init_player(t_config *op, t_sector *starting_sector);
void    	clamp_player_values(t_player *p, t_config op);
void		move(t_player *p, const Uint8 *state, double time);
void        look_around(t_player *p, const Uint8 *state, double time);
enum e_bool jumping(double ms_since_update, t_params pointer);
void        game_over(SDL_Surface *surface, t_config *op);
void        hurt_or_heal(t_player *p, const Uint8 *state);
void        draw_face(SDL_Surface *surface, t_hud *hud, t_player *p, t_config *op);
enum e_bool toggle_player_health(double ms_since_update, t_params pointer);

#endif
