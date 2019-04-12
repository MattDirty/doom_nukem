/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_sdl.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfatton <lfatton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 05:51:22 by lfatton           #+#    #+#             */
/*   Updated: 2019/04/12 05:51:36 by lfatton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_SDL_H
# define STRUCT_SDL_H

# include "SDL.h"

typedef struct			s_sdl
{
    SDL_Window			*window;
    SDL_Renderer		*renderer;
    SDL_Texture			*texture;
    SDL_Surface			*surface;
}						t_sdl;

#endif
