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

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <sys/stat.h>
#include "editor.h"
#include "editor_draw.h"
#include "editor_move_stuff.h"
#include "editor_panel_buttons.h"
#include "editor_mouse_clicks.h"
#include "bitmaps.h"
#include "textures.h"

static void	free_editor(t_editor *ed)
{
	free_map(ed->map);
	free_fonts(ed->fonts);
	free_sounds(ed->sounds);
	SDL_FreeSurface(ed->sdl.surface);
	SDL_DestroyRenderer(ed->sdl.renderer);
	SDL_DestroyWindow(ed->sdl.window);
}

void		quit_editor(t_editor *ed)
{
	free_editor(ed);
	TTF_Quit();
	SDL_Quit();
	exit(EXIT_SUCCESS);
}

static void	init_sdl_editor(Uint32 w, Uint32 h, char *name, t_editor *ed)
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0 || TTF_Init() < 0)
		error_doom("error: cannot run SDL");
	if (!(ed->sdl.window = SDL_CreateWindow(name, 0, 0, w, h, 0)))
		error_doom("Could not create window.");
	SDL_RaiseWindow(ed->sdl.window);
	if (!(ed->sdl.renderer = SDL_CreateRenderer(ed->sdl.window, -1, 0)))
		error_doom("Could not create renderer");
	if (!(ed->sdl.surface = SDL_CreateRGBSurface(0, w, h, 32, MASK_RED,
			MASK_GREEN, MASK_BLUE, MASK_ALPHA)))
		error_doom("Could not create surface.");
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
		error_doom((char *)Mix_GetError());
}

static void	init_editor(t_editor *ed)
{
	ed->zoom = EDITOR_ZOOM;
	ed->map_offset.x = DRAW_MAP_X;
	ed->map_offset.y = DRAW_MAP_Y;
	ed->selected.nodes = NULL;
	clear_selection(&ed->selected);
	ed->dragged.nodes = NULL;
	ed->state = e_null;
	ed->state_func[e_add_object] = &create_object_in_sector;
	ed->state_func[e_add_enemy] = &create_enemy_in_sector;
	ed->state_func[e_add_sector] = &try_sector_creation;
	ed->state_func[e_add_lever] = &try_lever_creation;
	ed->state_func[e_add_pickable] = &create_pickable_in_sector;
}

int			main(int ac, char **av)
{
	t_editor	ed;
	struct stat	buf;
	t_read_data	read_data;

	if (ac != 2)
		error_doom("Usage is : ./editor target_map_path");
	ft_bzero(&ed, sizeof(t_editor));
	ed.map_path = av[1];
	init_sdl_editor(EDITOR_W, EDITOR_H, "editor", &ed);
	init_editor(&ed);
	read_data.textures = &ed.textures;
	read_data.map = &ed.map;
	read_data.fonts = &ed.fonts;
	read_data.sounds = &ed.sounds;
	if ((stat(ed.map_path, &buf) < 0) && (ed.map_is_updated = e_false))
		read_file_editor("template.roflolilolmao", &read_data);
	else
	{
		read_file_editor(ed.map_path, &read_data);
		ed.map_is_updated = e_true;
	}
	init_panel(&ed.panel, ed.textures);
	ed.panel.buttons = NULL;
	editor_loop(&ed);
	return (0);
}
