/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fonts.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badhont <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 06:05:26 by badhont           #+#    #+#             */
/*   Updated: 2019/04/19 06:06:25 by badhont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOOMNUKEM_FONTS_H
# define DOOMNUKEM_FONTS_H

# include <SDL_ttf.h>

typedef struct	s_fonts
{
	TTF_Font	*horrendo120;
	TTF_Font	*sixty20;
	TTF_Font	*sixty40;
	TTF_Font	*amazdoom40;
	TTF_Font	*vcr20;
	TTF_Font	*vcr40;
}				t_fonts;

void			read_fonts_from_file(int fd, t_fonts **fonts);
void			write_fonts_to_file(int fd);
void			free_fonts(t_fonts *fonts);

#endif
