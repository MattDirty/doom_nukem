/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badhont <badhont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 19:44:24 by badhont           #+#    #+#             */
/*   Updated: 2019/04/14 18:30:57 by mtorsell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SDL.h"
#include "SDL_ttf.h"
#include "editor.h"
#include <sys/stat.h>
#include "editor_draw.h"
#include "editor_move_stuff.h"

void    init_sdl_editor(Uint32 w, Uint32 h, char *name, t_editor *ed)
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0 || TTF_Init() < 0 )
		error_doom("error: cannot run SDL");
    if (!(ed->sdl.window = SDL_CreateWindow(name, 0, 0, w, h, 0)))
        error_doom("Could not create window.");
	SDL_RaiseWindow(ed->sdl.window);
    if (!(ed->sdl.renderer = SDL_CreateRenderer(ed->sdl.window, -1, 0)))
        error_doom("Could not create renderer");
	if (!(ed->sdl.surface = SDL_CreateRGBSurface(0, w, h,
			32, MASK_RED, MASK_GREEN, MASK_BLUE, MASK_ALPHA)))
        error_doom("Could not create surface.");
    if (Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
        error_doom((char *)Mix_GetError());
}

int		event_editor(t_editor *ed)
{
    double      x;
    double      y;
	SDL_Event	ev;

	x = 0;
	y = 0;
    while (SDL_PollEvent(&ev))
    {
        if (ev.type == SDL_MOUSEMOTION)
        {
            x += ev.motion.xrel;
            y += ev.motion.yrel;
        }
        if (ev.key.keysym.scancode == SDL_SCANCODE_ESCAPE || ev.type == SDL_QUIT)
            exit(EXIT_SUCCESS);
        if (ev.type == SDL_MOUSEBUTTONDOWN && ev.button.button == SDL_BUTTON_LEFT)
            mousedown_action(ed, ev.button.x, ev.button.y);
        if (ev.type == SDL_MOUSEBUTTONUP && ev.button.button == SDL_BUTTON_LEFT)
            mouseup_action(ed, ev.button.x, ev.button.y);
    }
    if (ed->selected_nodes)
        move_walls_nodes(ed->selected_nodes, x, y);
    else if (ed->selected_player)
        move_player_spawn(ed->selected_player, x, y);
    else if (ed->selected_object)
    	move_object(ed->selected_object, x, y);
    return (1);
}

void	reframe_editor(t_editor *ed)
{
	SDL_Texture		*texture;

    draw_background(ed);
    draw_editor(ed);
    draw_panel(ed);
	SDL_RenderClear(ed->sdl.renderer);
	if (!(texture = SDL_CreateTextureFromSurface(ed->sdl.renderer, ed->sdl.surface)))
		error_doom("Could not create texture");
	SDL_RenderCopy(ed->sdl.renderer, texture, 0, 0);
    SDL_RenderPresent(ed->sdl.renderer);
    SDL_DestroyTexture(texture);
}

void	gameloop(t_editor *ed)
{
    reframe_editor(ed);
    ed->buttons.count = 1;
    while (1)
	{
        reframe_editor(ed);
        event_editor(ed);
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

int		main(int ac, char **av)
{
	t_editor			ed;
	struct stat         buf;
    t_read_data			read_data;

	if (ac != 2)
	    error_doom("Usage is : ./editor target_map_path");
	ft_bzero(&ed, sizeof(t_editor));
	ed.map_path = av[1];
    init_sdl_editor(EDITOR_W, EDITOR_H, "editor", &ed);
	if (stat(av[1], &buf) < 0)
    {
        ed.textures = load_textures();
	    ed.map = create_map(ed.textures);
        ed.fonts = load_fonts();
        ed.sounds = NULL;
    }
    else
    {
        read_data.textures = &ed.textures;
        read_data.map = &ed.map;
        read_data.fonts = &ed.fonts;
        read_data.sounds = &ed.sounds;
        read_file_editor(av[1], &read_data);
    }
    ed.selected_nodes = NULL;
    ed.selected_player = NULL;
    ed.selected_enemy = NULL;
    ed.selected_object = NULL;
    gameloop(&ed);
    return (0);
}
