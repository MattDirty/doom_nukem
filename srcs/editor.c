/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badhont <badhont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 19:44:24 by badhont           #+#    #+#             */
/*   Updated: 2019/04/12 03:09:11 by badhont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SDL.h"
#include "SDL_ttf.h"
#include "editor.h"
//#include "doom.h"
//#include "map.h"
//#include "serialisation.h"
//#include "libft.h"
#include "editor_draw.h"

void    init_sdl_editor(Uint32 w, Uint32 h, char *name, t_editor *ed)
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0 || TTF_Init() < 0)
		error_doom("error: cannot run SDL");
    if (!(ed->sdl.window = SDL_CreateWindow(name, 0, 0, w, h, SDL_WINDOW_FULLSCREEN_DESKTOP)))
        error_doom("Could not create window.");
	SDL_RaiseWindow(ed->sdl.window);
    if (!(ed->sdl.renderer = SDL_CreateRenderer(ed->sdl.window, -1, 0)))
        error_doom("Could not create renderer");
	if (!(ed->sdl.surface = SDL_CreateRGBSurface(0, w, h,
			32, MASK_RED, MASK_GREEN, MASK_BLUE, MASK_ALPHA)))
        error_doom("Could not create surface.");
}

int		event_editor(t_editor *ed)
{
	SDL_Event	ev;

    SDL_GetRelativeMouseState(&(ed->mouse_x), &(ed->mouse_y));
    SDL_PollEvent(&ev);
	if (ev.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
		exit(EXIT_SUCCESS);
    if (ev.type == SDL_MOUSEBUTTONDOWN && ev.button.button == SDL_BUTTON_LEFT)
	    click_on_pannel(ed, &ed->buttons, ev.button.x, ev.button.y);
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
    ed->buttons.count = 1;
    draw_pannel(ed);
	while (1)
	{
		if (event_editor(ed))
			reframe_editor(ed);
	}
}

t_fonts *load_fonts(void)
{
    t_fonts *fonts;

    if (!(fonts = (t_fonts *)malloc(sizeof(t_fonts))))
        error_doom("cannot alloc fonts");
    fonts->horrendo120 = TTF_OpenFont("fonts/horrendo.ttf", 120);
    fonts->sixty20 = TTF_OpenFont("fonts/sixty.ttf", 20);
    fonts->sixty40 = TTF_OpenFont("fonts/sixty.ttf", 40);
    if (!fonts->horrendo120 || !fonts->sixty20 || !fonts->sixty40)
        error_doom("Couldn't open fonts");
    return (fonts);
}

int		main(void)
{
	t_editor			ed;

	ft_bzero(&ed, sizeof(t_editor));
    ed.textures = load_textures();
    ed.map = create_map(ed.textures);

	write_file("mabite.roflolilolmao", ed.textures, ed.map);
	init_sdl_editor(EDITOR_W, EDITOR_H, "editor", &ed);

    ed.fonts = load_fonts();

    gameloop(&ed);

	printf("ta mere est une pute\n"); //j'aimerais que la norminette m'engueule.
    return (0);
}
