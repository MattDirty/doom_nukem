/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bitmaps.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfatton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 05:56:01 by lfatton           #+#    #+#             */
/*   Updated: 2019/04/19 06:08:08 by lfatton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include "bitmaps.h"
#include "doom.h"

t_sdl_surface_info 		read_header(int fd, int *pixels_size)
{
    t_sdl_surface_info 	info;
    char				buffer[124];
    int					pixels_offset;

    if (read(fd, &buffer, 2) <= 0 || buffer[0] != 'B' || buffer[1] != 'M')
        error_doom("nope");
    if (read(fd, pixels_size, sizeof(int)) <= 0)
        error_doom("mistaken bitmap assery");
    if (read(fd, buffer, 4) <= 0)
        error_doom("reserved cock");
    if (read(fd, &pixels_offset, sizeof(int)) <= 0)
        error_doom("pixels offet");
    if (pixels_offset != 138 || read(fd, buffer, pixels_offset - 14) <= 0)
        error_doom("Can't read a BITMAPV5HEADER.");
    *pixels_size -= pixels_offset;
    info.w = *((unsigned int*)&buffer[4]);
    info.h = *((unsigned int*)&buffer[8]);
    info.depth = *((unsigned int*)&buffer[20]) / info.h / info.w * 8;
    info.pitch = info.w * info.depth / 8;
    info.rmask = *((unsigned int*)&buffer[40]);
    info.gmask = *((unsigned int*)&buffer[44]);
    info.bmask = *((unsigned int*)&buffer[48]);
    info.amask = *((unsigned int*)&buffer[52]);
    return (info);
}

static inline int		shift_from_mask(Uint32 mask)
{
	if (mask == 0xff000000)
		return (24);
	if (mask == 0x00ff0000)
		return (16);
	if (mask == 0x0000ff00)
		return (8);
	if (mask == 0x000000ff)
		return (0);
	return (-1);
}

static inline void		swap_colors(Uint32 *pixel, t_sdl_surface_info  info)
{
    Uint32				alpha;
    Uint32				red;
    Uint32				green;
    Uint32				blue;

    if (info.amask == 0)
        alpha = 0xff;
    else
        alpha = ((*pixel & info.amask) >> shift_from_mask(info.amask))
            << AMASK_SHIFT;
    red = ((*pixel & info.rmask) >> shift_from_mask(info.rmask))
        << RMASK_SHIFT;
    green = ((*pixel & info.gmask) >> shift_from_mask(info.gmask))
        << GMASK_SHIFT;
    blue = ((*pixel & info.bmask) >> shift_from_mask(info.bmask))
        << BMASK_SHIFT;
    *pixel = alpha | red | green | blue;
}

static inline void		reorder_colors(Uint32 *pixels, t_sdl_surface_info  info)
{
	int					i;
	int					j;
	int					swap;
	int					size;

	size = info.w * info.h;
	i = 0;
	while (i < size)
	{
		swap_colors(pixels + i, info);
		i++;
	}
	i = 0;
	while (i < info.h / 2)
	{
		j = 0;
		while (j < info.w)
		{
			swap = pixels[i * info.w + j];
			pixels[i * info.w + j] = pixels[(info.h - i - 1) * info.w + j];
			pixels[(info.h - i - 1) * info.w + j] = swap;
			j++;
		}
		i++;
	}
}

SDL_Surface				*load_bmp(char *path)
{
	int					fd;
	t_sdl_surface_info	info;
	int					pixels_size;
	SDL_Surface			*ret;
	char				*pixels;

	fd = open(path, O_RDONLY);
	info = read_header(fd, &pixels_size);
	if (info.depth != 32)
		error_doom("Only 32 bits depth bitmaps can be used");
	if (!(pixels = malloc(pixels_size)))
		error_doom("buy some more ram plz");
	if (read(fd, pixels, pixels_size) <= 0)
		error_doom("yeah well too bad");
	close(fd);
	reorder_colors((Uint32*)pixels, info);
	ret = SDL_CreateRGBSurfaceFrom(pixels, info.w, info.h, info.depth,
			info.pitch, TARGET_RMASK, TARGET_GMASK, TARGET_BMASK, TARGET_AMASK);
	if (ret == NULL)
		error_doom("I've done all I could but it wasn't enough");
	ret->userdata = path;
	return (ret);
}
