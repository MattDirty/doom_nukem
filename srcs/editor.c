/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badhont <badhont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 19:44:24 by badhont           #+#    #+#             */
/*   Updated: 2019/04/12 06:17:55 by lfatton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"
#include "editor_draw.h"

void    init_sdl_editor(Uint32 w, Uint32 h, char *name, t_sdl *sdl)
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		error_doom("error: cannot run SDL");
    if (!(sdl->window = SDL_CreateWindow(name, 0, 0, w, h, 0)))
        error_doom("Could not create window.");
	SDL_RaiseWindow(sdl->window);
    if (!(sdl->renderer = SDL_CreateRenderer(sdl->window, -1, 0)))
        error_doom("Could not create renderer");
	if (!(sdl->surface = SDL_CreateRGBSurface(0, w, h,
			32, MASK_RED, MASK_GREEN, MASK_BLUE, MASK_ALPHA)))
        error_doom("Could not create surface.");
}

int		event_editor(t_editor *ed)
{
	(void)ed;
	SDL_Event	event;

	SDL_PollEvent(&event);
	if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
		exit(EXIT_SUCCESS);
	return (1);
}

void	reframe_editor(t_editor *ed)
{
	SDL_Texture		*texture;

	draw_editor(ed);
	SDL_RenderClear(ed->sdl.renderer);
	if (!(texture = SDL_CreateTextureFromSurface(ed->sdl.renderer, ed->sdl.surface)))
		error_doom("Could not create texture");
	SDL_RenderCopy(ed->sdl.renderer, texture, 0, 0);
	SDL_DestroyTexture(texture);
	SDL_RenderPresent(ed->sdl.renderer);
}

void	gameloop(t_editor *ed)
{
	reframe_editor(ed);
	while (1)
	{
		if (event_editor(ed))
			reframe_editor(ed);
	}
}

int		main(void)
{
	t_editor			ed;

	ft_bzero(&ed, sizeof(t_editor));
    ed.textures = load_textures();
    ed.map = create_map(ed.textures);

	write_file("mabite.roflolilolmao", ed.textures, ed.map);
	init_sdl_editor(E_WIN_W, E_WIN_H, "editor", &ed.sdl);

	gameloop(&ed);

	printf("ta mere est une pute\n"); //j'aimerais que la norminette m'engueule.
    return (0);
}
