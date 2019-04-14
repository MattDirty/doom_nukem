/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfatton <lfatton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 01:04:26 by lfatton           #+#    #+#             */
/*   Updated: 2019/03/19 16:17:21 by lfatton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "SDL.h"
#include "SDL_ttf.h"
#include "libft.h"
#include "doom.h"
#include "default.h"
#include "map.h"
#include "fonts.h"
#include "textures.h"
#include "sounds.h"

void        error_doom(char *err)
{
    ft_putendl(err);
    exit(EXIT_FAILURE);
}

int         quit_doom(t_env *e)
{
	SDL_FreeSurface(e->doom.surface);
	SDL_DestroyTexture(e->doom.texture);
	SDL_DestroyRenderer(e->doom.renderer);
	SDL_DestroyWindow(e->doom.window);
	TTF_Quit();
	SDL_Quit();
    exit(EXIT_SUCCESS);
	return (0);
}
