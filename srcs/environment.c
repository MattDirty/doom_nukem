/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfatton <lfatton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 01:04:26 by lfatton           #+#    #+#             */
/*   Updated: 2019/03/08 19:18:16 by lfatton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void		error_doom(char *err)
{
	ft_putendl(err);
	exit(EXIT_FAILURE);
}

int			quit_doom(t_env *e)
{
	SDL_FreeSurface(e->surf);
	SDL_DestroyTexture(e->text);
	SDL_DestroyRenderer(e->render);
	SDL_DestroyWindow(e->win);
	SDL_Quit();
	free(e->p);
	free(e->r);
	free(e);
	exit(EXIT_SUCCESS);
	return (0);
}

static void	init_player(t_env *e)
{
	e->p->height = HALF_H;
	e->p->heading = WEST;
	e->p->pos.y = 2;
	e->p->pos.x = 2;
}

void		init_doom(t_env *e)
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		error_doom("error: cannot run SDL");
	if (SDL_CreateWindowAndRenderer(WIN_W, WIN_H, 0,
			&e->win, &e->render) < 0)
		error_doom("error: cannot create window");
	SDL_SetWindowPosition(e->win, DEBUG_W + 5, SDL_WINDOWPOS_CENTERED)
//	if (SDL_SetRelativeMouseMode(SDL_TRUE) > 0)
//		error_doom("error: cannot hide mouse cursor");
	if (!(e->surf = SDL_CreateRGBSurface(0, WIN_W, WIN_H, 32, 0, 0, 0, 0)))
		error_doom("error: cannot create surface");
	init_player(e);
}
