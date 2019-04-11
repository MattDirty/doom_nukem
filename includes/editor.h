#ifndef DOOMNUKEM_EDITOR_H
# define DOOMNUKEM_EDITOR_H

#include <unistd.h>
#include <stdio.h> // TO DELETE !!!
#include <math.h>

#include "SDL.h"
#include "doom.h"
#include "serialisation.h"
# include "textures.h"
# include "map.h"
# include "walls.h"
#include "default.h"
#include "surface_manipulation.h"

# define EDITOR_W 800
# define EDITOR_H 640
# define EDITOR_W_H (EDITOR_W / 2)
# define EDITOR_H_H (EDITOR_H / 2)
# define EDITOR_ZOOM 20

typedef struct			s_sdl_editor
{
    SDL_Window			*window;
    SDL_Renderer		*renderer;
    SDL_Surface         *surface;
}						t_sdl_editor;

typedef struct			s_button
{
	t_rect				rect;
	void				*funct;
}						t_button;

typedef struct			s_buttons
{
    int                 count;
	t_button			items[1];
}						t_buttons;

typedef struct          s_editor
{
	t_sdl			sdl;
    t_map			*map;
    t_textures      *textures;
}                       t_editor;

t_map		*create_map(t_textures *textures);
t_textures	*load_textures(void);

#endif
