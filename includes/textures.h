#ifndef DOOMNUKEM_TEXTURES_H
#define DOOMNUKEM_TEXTURES_H

#include "SDL.h"

#define BITMAP_DEPTH 32

typedef struct				s_texture_node
{
    SDL_Surface				*texture;
    struct s_texture_node	*next;
}							t_texture_node;

typedef struct				s_textures
{
    t_texture_node			*first;
}							t_textures;

/**
 ** This type exists only to satisfy the stupid norm, since
 ** 9 local variables are required to read the parameters of
 ** SDL_CreateRGBSurfaceFrom.
 **/
typedef struct				s_SDL_Surface_info
{
    int						w;
    int						h;
    Uint8					depth;
    int						pitch;
    Uint32					Rmask;
    Uint32					Gmask;
    Uint32					Bmask;
    Uint32					Amask;
}							t_SDL_Surface_info;
int	find_texture_by_name(
        t_textures *textures,
        char *name,
        SDL_Surface **texture);
int	add_bitmap_file_to_textures(
        t_textures *textures,
        char *path);

int	read_textures_from_file(int fd, t_textures **textures);
int	write_textures_to_file(int fd, t_textures *textures);

int	read_texture_node_from_file(int fd, t_texture_node **texture_node);
int	write_texture_node_to_file(int fd, t_texture_node *texture_node);

#endif
