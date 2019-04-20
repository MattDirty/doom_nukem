/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtorsell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/20 03:20:53 by mtorsell          #+#    #+#             */
/*   Updated: 2019/04/20 03:20:59 by mtorsell         ###   ########.fr       */
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

void		find_texture_from_file(
		int fd, t_textures *textures, SDL_Surface **surface)
{
	char *name;

	read_str_from_file(fd, &name);
	find_texture_by_name(textures, name, surface);
	free(name);
}

void		free_textures(t_textures *textures)
{
	t_texture_node *n;
	t_texture_node *p;

	n = textures->first;
	while (n)
	{
		p = n;
		n = n->next;
		free(p->texture->pixels);
		free(p->texture->userdata);
		SDL_FreeSurface(p->texture);
		free(p);
	}
	free(textures);
}

void		add_texture(t_textures *textures, t_texture_node *new_node)
{
	t_texture_node *node;

	node = textures->first;
	if (!node)
	{
		textures->first = new_node;
		return ;
	}
	while (1)
	{
		if (!node->next)
		{
			node->next = new_node;
			return ;
		}
		node = node->next;
	}
}

void		find_texture_by_name(t_textures *textures, char *name,
				SDL_Surface **texture)
{
	t_texture_node *node;

	node = textures->first;
	if (!node)
		error_doom("can't find texture in NULL textures");
	while (node)
	{
		if (ft_strcmp(node->texture->userdata, name) == 0)
		{
			*texture = node->texture;
			return ;
		}
		node = node->next;
	}
	error_doom("can't find texture in textures");
}

void		add_bitmap_file_to_textures(t_textures *textures, char *path)
{
	SDL_Surface		*texture;
	t_texture_node	*node;

	texture = load_bmp(path);
	if (!texture)
		error_doom("can't open bmp");
	if (!(node = (t_texture_node *)malloc(sizeof(t_texture_node))))
		error_doom("can't malloc t_texture_node");
	node->texture = texture;
	node->next = NULL;
	add_texture(textures, node);
}
