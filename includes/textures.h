#ifndef TEXTURES_H
# define TEXTURES_H

# include <SDL.h>

# define BITMAP_DEPTH 32

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

void	free_textures(t_textures *textures);
void	find_texture_by_name(
        t_textures *textures,
        char *name,
        SDL_Surface **texture);
void	add_bitmap_file_to_textures(
        t_textures *textures,
        char *path);

void	read_textures_from_file(int fd, t_textures **textures);
void	write_textures_to_file(int fd, t_textures *textures);

void	read_texture_node_from_file(int fd, t_texture_node **texture_node);
void	write_texture_node_to_file(int fd, t_texture_node *texture_node);

void	find_texture_from_file(int fd, t_textures *textures, SDL_Surface **surface);

void	add_texture(t_textures *textures, t_texture_node *new_node);

#endif
