/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_draw.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfatton <lfatton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 05:45:21 by lfatton           #+#    #+#             */
/*   Updated: 2019/04/12 05:45:33 by lfatton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EDITOR_DRAW_H
# define EDITOR_DRAW_H

# include "map.h"
# include "struct_sdl.h"
# include "editor.h"

# define WHITE 0xFFFFFFFF
# define RED 0xFFFF0000
# define PINK 0xFFFFAAAA
# define GREEN 0xFF00FF00
# define BLUE 0xFF0000FF


void		draw_editor(t_editor *ed);

#endif
