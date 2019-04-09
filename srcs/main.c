#include "SDL.h"
#include "SDL_mixer.h"
#include "doom.h"
#include "map.h"
#include "debug.h"
#include "config.h"
#include "default.h"
#include "serialisation.h"

t_sdl       init_sdl(Uint32 w, Uint32 h, Uint32 fullscreen, char *name)
{
    t_sdl   sdl;

    if (fullscreen)
        fullscreen = SDL_WINDOW_FULLSCREEN_DESKTOP;
    if (!(sdl.window = SDL_CreateWindow(name, 0, 0,
            w, h, fullscreen)))
        error_doom("Could not create window.");
    if (!(sdl.renderer = SDL_CreateRenderer(sdl.window, -1, 0)))
        error_doom("Could not create renderer");
    if (!(sdl.texture = SDL_CreateTexture(sdl.renderer,
            SDL_PIXELFORMAT_ARGB32, SDL_TEXTUREACCESS_TARGET,
            w, h)))
        error_doom("Could not create texture.");
    if (!(sdl.surface = SDL_CreateRGBSurface(0, w, h,
            32, MASK_RED, MASK_GREEN, MASK_BLUE, MASK_ALPHA)))
        error_doom("Could not create surface.");
    if (Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
    	error_doom((char *)Mix_GetError());

	return (sdl);
}

int		main (int ac, char **av)
{
	t_env		e;
    t_textures	*textures;

	e.op = load_config();
    if (ac > 1 && ft_strcmp(av[1], "debug") == 0)
		e.debug_mode = t_true;
	else
		e.debug_mode = t_false;
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
		error_doom("error: cannot run SDL");
	e.doom = init_sdl(e.op.win_w, e.op.win_h, e.op.fullscreen, "Doom_Nukem");
	if (!(e.music = Mix_LoadMUS("sounds/lamerde.wav")))
		error_doom("Couldn't open lamerde.wav");
	if (SDL_SetRelativeMouseMode(SDL_TRUE) > 0)
		error_doom("error: cannot hide mouse cursor");
    if (read_file("mabite.roflolilolmao", &textures, &e.map) < 0)
        error_doom("Could not load game file");
	e.p = init_player(&e.op, &e.map->sectors->items[0]);
    e.p.weapons = allocate_weapons();
    if (e.debug_mode)
		e.debug = init_sdl(DEBUG_W, DEBUG_H, 0, "debug");
	loop_doom(&e);
    free(textures);
	return (EXIT_SUCCESS);
}
