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

void        error_doom(char *err)
{
    ft_putendl(err);
    exit(EXIT_FAILURE);
}

int         quit_doom(t_env *e)
{
    SDL_FreeSurface(e->doom->surface);
    SDL_DestroyTexture(e->doom->texture);
    SDL_DestroyRenderer(e->doom->renderer);
    SDL_DestroyWindow(e->doom->window);
    SDL_Quit();
    free(e->p);
    free(e->sector);
    free(e->doom);
    free(e);
    exit(EXIT_SUCCESS);
    return (0);
}

static void init_player(t_player *p)
{
    p->vision_height = HALF_H;
    p->heading = WEST;
    p->pos.y = 2;
    p->pos.x = 3;
    p->speed.x = 0;
    p->speed.y = 0;
    p->weapon = SDL_LoadBMP("dwa.bmp");
}

void        init_doom(t_env *e)
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
        error_doom("error: cannot run SDL");
    if (SDL_CreateWindowAndRenderer(WIN_W, WIN_H, 0,
                                    &e->doom->window, &e->doom->renderer) < 0)
        error_doom("error: cannot create window");
    SDL_SetWindowPosition(e->doom->window, WIN_W + 70, SDL_WINDOWPOS_CENTERED);
    if (SDL_SetRelativeMouseMode(SDL_TRUE) > 0)
        error_doom("error: cannot hide mouse cursor");
    if (!(e->doom->surface = SDL_CreateRGBSurface(0, WIN_W, WIN_H,
                                                  32, MASK_RED, MASK_GREEN, MASK_BLUE, MASK_ALPHA)))
        error_doom("error: cannot create surface");
    init_player(e->p);
}
