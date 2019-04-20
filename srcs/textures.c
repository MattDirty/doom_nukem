/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtorsell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/20 03:18:22 by mtorsell          #+#    #+#             */
/*   Updated: 2019/04/20 03:18:35 by mtorsell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <errno.h>
#include <SDL.h>
#include "libft.h"
#include "textures.h"
#include "bitmaps.h"
#include "serialisation.h"
#include "doom.h"

void	read_textures_from_file(int fd, t_textures **textures)
{
	int				count;
	int				i;
	t_texture_node	*node;
	t_texture_node	*previous;

	if (!(*textures = (t_textures *)malloc(sizeof(t_textures))))
		error_doom("can't malloc t_textures");
	if (!read(fd, &count, sizeof(count)))
		error_doom("can't read textures count");
	previous = NULL;
	i = 0;
	while (i < count)
	{
		read_texture_node_from_file(fd, &node);
		if (previous)
			previous->next = node;
		else
			(*textures)->first = node;
		previous = node;
		i++;
	}
}

void	write_textures_to_file(int fd, t_textures *textures)
{
	int				count;
	t_texture_node	*node;

	count = 0;
	node = textures->first;
	while (1)
	{
		if (!node)
			break ;
		count++;
		node = node->next;
	}
	if (write(fd, &count, sizeof(count)) < 0)
		error_doom("can't write textures count");
	count = 0;
	node = textures->first;
	while (1)
	{
		if (!node)
			break ;
		write_texture_node_to_file(fd, node);
		node = node->next;
		count++;
	}
}

void	read_masks(int fd, t_sdl_surface_info *info)
{
	if (!read(fd, &info->rmask, sizeof(info->rmask)))
		error_doom("can't read info.rmask");
	if (!read(fd, &info->gmask, sizeof(info->gmask)))
		error_doom("can't read info.gmask");
	if (!read(fd, &info->bmask, sizeof(info->bmask)))
		error_doom("can't read info.bmask");
	if (!read(fd, &info->amask, sizeof(info->amask)))
		error_doom("can't read info.amask");
}

void	read_texture_node_from_file(int fd, t_texture_node **texture_node)
{
	t_sdl_surface_info	info;
	void				*pixels;

	if (!(*texture_node = (t_texture_node *)malloc(sizeof(t_texture_node))))
		error_doom("can't malloc t_texture_node");
	(*texture_node)->next = NULL;
	if (!read(fd, &info.w, sizeof(info.w)))
		error_doom("can't read info.w");
	if (!read(fd, &info.h, sizeof(info.h)))
		error_doom("can't read info.h");
	if (!read(fd, &info.depth, sizeof(info.depth)))
		error_doom("can't read info.depth");
	if (!read(fd, &info.pitch, sizeof(info.pitch)))
		error_doom("can't read info.pitch");
	read_masks(fd, &info);
	if (!(pixels = malloc(info.depth / 8 * info.w * info.h)))
		error_doom("can't malloc pixels");
	if (read(fd, pixels, info.depth / 8 * info.w * info.h) <= 0)
		error_doom("can't read pixels");
	if (!((*texture_node)->texture = SDL_CreateRGBSurfaceFrom(
				pixels, info.w, info.h, info.depth, info.pitch, info.rmask,
				info.gmask, info.bmask, info.amask)))
		error_doom("sdl couldn't create surface");
	read_str_from_file(fd, (char **)&(*texture_node)->texture->userdata);
}

void	write_texture_node_to_file(int fd, t_texture_node *texture_node)
{
	SDL_Surface		*texture;
	SDL_PixelFormat	format;

	texture = texture_node->texture;
	format = *(texture->format);
	if (write(fd, &(texture->w), sizeof(texture->w)) <= 0)
		error_doom("couldn't write texture w");
	if (write(fd, &(texture->h), sizeof(texture->h)) <= 0)
		error_doom("couldn't write texture h");
	if (write(fd, &(format.BitsPerPixel), sizeof(format.BitsPerPixel)) <= 0)
		error_doom("couldn't write texture BitsPerPixel");
	if (write(fd, &(texture->pitch), sizeof(texture->pitch)) <= 0)
		error_doom("couldn't write texture pitch");
	if (write(fd, &(format.Rmask), sizeof(format.Rmask)) <= 0)
		error_doom("couldn't write texture Rmask");
	if (write(fd, &(format.Gmask), sizeof(format.Gmask)) <= 0)
		error_doom("couldn't write texture Gmask");
	if (write(fd, &(format.Bmask), sizeof(format.Bmask)) <= 0)
		error_doom("couldn't write texture Bmask");
	if (write(fd, &(format.Amask), sizeof(format.Amask)) <= 0)
		error_doom("couldn't write texture amask");
	if (write(fd, texture->pixels,
			format.BytesPerPixel * texture->w * texture->h) <= 0)
		error_doom("couldn't write pixels");
	write_str_to_file(fd, texture->userdata);
}
