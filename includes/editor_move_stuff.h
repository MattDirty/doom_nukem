/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_move_stuff.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badhont <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 04:45:53 by badhont           #+#    #+#             */
/*   Updated: 2019/04/19 04:46:25 by badhont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EDITOR_MOVE_STUFF_H
# define EDITOR_MOVE_STUFF_H

void	move_map(t_editor *ed, SDL_Scancode key);
void	move_walls_nodes(t_editor *ed, double x, double y);
void	move_player_spawn(t_editor *ed, double x, double y);
void	move_object(t_editor *ed, double x, double y);
void	move_enemy(t_editor *ed, double x, double y);
void	move_pickable(t_editor *ed, double x, double y);

#endif
