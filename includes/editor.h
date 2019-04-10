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
# define EDITOR_ZOOM 2

typedef struct			s_sdl_editor
{
    SDL_Window			*window;
    SDL_Renderer		*renderer;
    SDL_Surface         *surface;
}						t_sdl_editor;

/*typedef struct          s_editor
{
	t_sdl			sdl;
    t_map			*map;
}                       t_editor;*/


/*int	read_file(char *filename, t_textures **textures, t_map **map);
void	write_file(char *filename, t_textures *textures, t_map *map);

int	read_str_from_file(int fd, char **name);
int	write_str_to_file(int fd, char *name);*/

#endif
