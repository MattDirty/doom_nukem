/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_sdl.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badhont <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 09:22:55 by badhont           #+#    #+#             */
/*   Updated: 2019/04/19 09:23:47 by badhont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOOMNUKEM_STRUCT_SDL_H
# define DOOMNUKEM_STRUCT_SDL_H

# include <SDL.h>

typedef	struct			s_sdl
{
	SDL_Window			*window;
	SDL_Renderer		*renderer;
	SDL_Texture			*texture;
	SDL_Surface			*surface;
}						t_sdl;

#endif
