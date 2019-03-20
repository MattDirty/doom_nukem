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

#include "libft.h"
#include <stdlib.h>
#include "doom.h"
#include "default.h"

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
	SDL_Quit();
    exit(EXIT_SUCCESS);
	return (0);
}

void        init_doom(t_env *e)
{
    if (SDL_SetRelativeMouseMode(SDL_TRUE) > 0)
        error_doom("error: cannot hide mouse cursor");
    e->p = init_player(&e->op);
}
