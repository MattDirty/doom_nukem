/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bitmaps.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badhont <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 02:13:45 by badhont           #+#    #+#             */
/*   Updated: 2019/04/19 02:14:31 by badhont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITMAPS_H
# define BITMAPS_H

# include <SDL.h>

# define TARGET_AMASK 0x000000ff
# define TARGET_RMASK 0xff000000
# define TARGET_GMASK 0x00ff0000
# define TARGET_BMASK 0x0000ff00
# define AMASK_SHIFT 0
# define RMASK_SHIFT 24
# define GMASK_SHIFT 16
# define BMASK_SHIFT 8

SDL_Surface	*load_bmp(char *path);

#endif
