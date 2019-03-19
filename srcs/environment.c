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
	// int i;
	// t_segment s;

	SDL_FreeSurface(e->doom->surface);
	SDL_DestroyTexture(e->doom->texture);
	SDL_DestroyRenderer(e->doom->renderer);
	SDL_DestroyWindow(e->doom->window);
	SDL_Quit();

	// i = 0;
	// while (i < map->sectors.count)
	// {
		// s = map->sectors->items[i];
		// free(s.walls->items);
		// i++;
	// }
	// free(map->sectors->items);
	// free(map);

	free(e->p);
	free(e->doom);
	free(e);
	exit(EXIT_SUCCESS);
	return (0);
}

void        init_doom(t_env *e)
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
        error_doom("error: cannot run SDL");
    if (e->debug_mode == t_true)
    {
        if (SDL_CreateWindowAndRenderer(WIN_W, WIN_H, 0,
                &e->doom->window, &e->doom->renderer) < 0)
            error_doom("error: cannot create window");
        printf("debug");
    }
    else
    {
        if (SDL_CreateWindowAndRenderer(WIN_W, WIN_H, SDL_WINDOW_FULLSCREEN,
                &e->doom->window, &e->doom->renderer) < 0)
            error_doom("error: cannot create window");
    }
    SDL_SetWindowPosition(e->doom->window, 30, 0);
    if (SDL_SetRelativeMouseMode(SDL_TRUE) > 0)
        error_doom("error: cannot hide mouse cursor");
    if (!(e->doom->surface = SDL_CreateRGBSurface(0, WIN_W, WIN_H,
            32, MASK_RED, MASK_GREEN, MASK_BLUE, MASK_ALPHA)))
        error_doom("error: cannot create surface");
    init_player(e->p);
}
