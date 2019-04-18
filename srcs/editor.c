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
#include "editor.h"
#include <sys/stat.h>
#include "editor_draw.h"
#include "editor_move_stuff.h"
#include "editor_panel_buttons.h"
#include "bitmaps.h"
#include "textures.h"

static void    free_editor(t_editor *ed)
{
    SDL_FreeSurface(ed->sdl.surface);
    SDL_DestroyRenderer(ed->sdl.renderer);
    SDL_DestroyWindow(ed->sdl.window);
}

void    quit_editor(t_editor *ed)
{
    free_editor(ed);
    TTF_Quit();
    SDL_Quit();
    exit(EXIT_SUCCESS);
}

void	clear_selection(t_selected_elements *selected)
{
	selected->nodes = NULL;
	selected->p_spawn = NULL;
	selected->enemy = NULL;
	selected->object = NULL;
	selected->sector = NULL;
	selected->wall = NULL;
    selected->pickable = NULL;
}

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

t_fonts *load_fonts(void)
{
    t_fonts *fonts;

    if (!(fonts = (t_fonts *)malloc(sizeof(t_fonts))))
        error_doom("cannot alloc fonts");
    fonts->horrendo120 = TTF_OpenFont("fonts/horrendo.ttf", 120);
    fonts->sixty20 = TTF_OpenFont("fonts/sixty.ttf", 20);
    fonts->sixty40 = TTF_OpenFont("fonts/sixty.ttf", 40);
    fonts->amazdoom40 = TTF_OpenFont("fonts/amazdoom.ttf", 40);
	fonts->vcr20 = TTF_OpenFont("fonts/vcr_mono.ttf", 20);
	fonts->vcr40 = TTF_OpenFont("fonts/vcr_mono.ttf", 40);
    if (!fonts->horrendo120 || !fonts->sixty20 || !fonts->sixty40
        || !fonts->amazdoom40 || !fonts->vcr20 || !fonts->vcr40)
        error_doom("Couldn't open fonts");
    return (fonts);
}

void    create_sub_lists(t_textures *textures, t_panel *panel)
{
    t_texture_node	*node;
    t_texture_node	*new_node;
    char            **str;

    node = textures->first;
	panel->skies.first = NULL;
	panel->walls.first = NULL;
	panel->flats.first = NULL;
	panel->weapons.first = NULL;
	panel->wall_objects.first = NULL;
    while (node)
    {
		if (!(new_node = (t_texture_node *)malloc(sizeof(t_texture_node))))
			error_doom("Couldn't malloc new node");
		new_node->texture = node->texture;
		new_node->next = NULL;
        str = ft_strsplit(node->texture->userdata, '/');
        if (ft_strcmp(str[1], "skybox") == 0)
            add_texture(&panel->skies, new_node);
		else if (ft_strcmp(str[1], "walls") == 0)
			add_texture(&panel->walls, new_node);
		else if (ft_strcmp(str[1], "flats") == 0)
			add_texture(&panel->flats, new_node);
		else if (ft_strcmp(str[1], "wall_objects") == 0)
			add_texture(&panel->wall_objects, new_node);
        else if (!ft_strcmp(str[2], "gun.bmp") || !ft_strcmp(str[2],
                "shotgun.bmp") || !ft_strcmp(str[2], "vacuum.bmp"))
            add_texture(&panel->weapons, new_node);
        node = node->next;
    }
}

void    init_panel(t_panel *panel, t_textures *textures)
{
	if (!(panel->surface = SDL_CreateRGBSurface(
            0, PANEL_W, PANEL_H, 32,
            MASK_RED, MASK_GREEN, MASK_BLUE, MASK_ALPHA))) {
		error_doom("Couldn't create Panel Surface");
	}
    create_sub_lists(textures, panel);
	panel->buttons = NULL;
}

t_sounds *load_sounds(void)
{
    t_sounds    *sounds;

    if (!(sounds = (t_sounds *)malloc(sizeof(t_sounds))))
        error_doom("cannot alloc sounds");
    if (!(sounds->lamerde = Mix_LoadMUS("sounds/lamerde.wav")))
        error_doom("error: cannot load lamerde.wav");
    if (!(sounds->zap = Mix_LoadWAV("sounds/zap.wav")))
        error_doom("error: cannot load zap.wav");
    if (!(sounds->fu_bitch = Mix_LoadWAV("sounds/fu_bitch.wav")))
        error_doom("error: cannot load fu_bitch.wav");
    if (!(sounds->xplosion = Mix_LoadWAV("sounds/xplosion.wav")))
        error_doom("error: cannot load xplosion.wav");
    if (!(sounds->mwiiicrkk = Mix_LoadWAV("sounds/mwiiicrkk.wav")))
        error_doom("error: cannot load mmwiiicrkk.wav");
    if (!(sounds->mip_mep = Mix_LoadWAV("sounds/mip_mep.wav")))
        error_doom("error: cannot load mip_mep.wav");
    if (!(sounds->meeeh = Mix_LoadWAV("sounds/meeeh.wav")))
        error_doom("error: cannot load meeeh.wav");
    if (!(sounds->pew = Mix_LoadWAV("sounds/pew_crk_crk.wav")))
        error_doom("error: cannot load pew.wav");
    if (!(sounds->slurp = Mix_LoadWAV("sounds/slurp_vrrrr_krrkrkrkrkrkr.wav")))
        error_doom("error: cannot load surlp.wav");
    if (!(sounds->yeee = Mix_LoadWAV("sounds/yeee.wav")))
        error_doom("error: cannot load yeee.wav");
    return (sounds);
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
    ed.zoom = EDITOR_ZOOM;
    ed.map_offset.x = DRAW_MAP_X;
    ed.map_offset.y = DRAW_MAP_Y;
	if (stat(av[1], &buf) < 0)
	{
		ed.textures = load_textures();
		ed.map = create_map(ed.textures);
		ed.fonts = load_fonts();
		ed.sounds = load_sounds();
        ed.map_is_updated = e_false;
    }
    else
	{
		read_data.textures = &ed.textures;
		read_data.map = &ed.map;
		read_data.fonts = &ed.fonts;
		read_data.sounds = &ed.sounds;
		read_file_editor(av[1], &read_data);
        ed.map_is_updated = e_true;
    }
	init_panel(&ed.panel, ed.textures);
	clear_selection(&ed.selected);
    free_buttons_list(ed.panel.buttons);
    ed.panel.buttons = NULL;
    clear_selection(&ed.dragged);
    ed.state = e_null;
    ed.state_func[e_add_object] = &create_object_in_sector;
    ed.state_func[e_add_enemy] = &create_enemy_in_sector;
    ed.state_func[e_add_sector] = &try_sector_creation;
    editor_loop(&ed);
    return (0);
}
