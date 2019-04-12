/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   surface_manipulation.h                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfatton <lfatton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 05:51:43 by lfatton           #+#    #+#             */
/*   Updated: 2019/04/12 05:51:52 by lfatton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SURFACE_MANIPULATION_H
# define SURFACE_MANIPULATION_H

# include "SDL.h"
# include "e_bool.h"
# include "utils.h"

Uint32		get_pixel(SDL_Surface *s, int x, int y, enum e_bool force_alpha);

void		put_pixel(SDL_Surface *s, int x, int y, Uint32 color);
void	    put_pixel_alpha(SDL_Surface *s, int x, int y, Uint32 color);

void		draw_circle(SDL_Surface *surface, t_coords center, int r, Uint32 color);
void		draw_circle_filled(SDL_Surface *surface, t_coords center, int r, Uint32 color);
void        draw_segment(SDL_Surface *surface, t_segment segment, Uint32 color);

void        print_surface(SDL_Renderer *r, SDL_Surface *surf);

#endif
