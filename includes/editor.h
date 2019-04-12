/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfatton <lfatton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 05:45:39 by lfatton           #+#    #+#             */
/*   Updated: 2019/04/12 05:48:52 by lfatton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EDITOR_H
# define EDITOR_H

# include <unistd.h>
# include <stdio.h> // TO DELETE !!!
# include <math.h>

# include "SDL.h"
# include "doom.h"
# include "serialisation.h"
# include "textures.h"
# include "map.h"
# include "walls.h"
# include "default.h"
# include "surface_manipulation.h"

# define E_WIN_W 800
# define E_WIN_H 640
# define E_HALF_W (E_WIN_W / 2)
# define E_HALF_H (E_WIN_H / 2)
# define EDITOR_ZOOM 20

typedef struct		s_sdl_editor
{
    SDL_Window		*window;
    SDL_Renderer	*renderer;
    SDL_Surface		*surface;
}			t_sdl_editor;

typedef struct		s_editor
{
	t_sdl		sdl;
	t_map		*map;
	t_textures	*textures;
}			t_editor;

t_map			*create_map(t_textures *textures);
t_textures		*load_textures(void);

#endif
