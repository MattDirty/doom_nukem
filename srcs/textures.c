#include <unistd.h>
#include <errno.h>

#include "SDL.h"
#include "libft.h"

#include "textures.h"
#include "serialisation.h"
#include "doom.h"

void	add_texture(t_textures *textures, t_texture_node *new_node)
{
    t_texture_node	*node;
    
    node = textures->first;
    if (!node)
    {
        textures->first = new_node;
        return;
    }
    while (1)
    {
        if (!node->next)
        {
            node->next = new_node;
            return;
        }
        node = node->next;
    }
}

void	find_texture_by_name(
        t_textures *textures,
        char *name,
        SDL_Surface **texture)
{
    t_texture_node	*node;

    node = textures->first;
    if (!node)
        error_doom("can't find texture in NULL textures");
    while (node)
    {
        if (ft_strcmp(node->texture->userdata, name) == 0)
        {
            *texture = node->texture;
            return;
        }
        node = node->next;
    }
    error_doom("can't find texture in textures");
}

void	add_bitmap_file_to_textures(
        t_textures *textures,
        char *path)
{
    SDL_Surface		*texture;
    t_texture_node	*node;

    texture = SDL_LoadBMP(path);
    if (!texture)
        error_doom("can't open bmp");
    if (!(node = (t_texture_node*)malloc(sizeof(t_texture_node))))
        error_doom("can't malloc t_texture_node");
    texture->userdata = path;
    node->texture = texture;
    node->next = NULL;
    add_texture(textures, node);
}

void	read_textures_from_file(int fd, t_textures **textures)
{
    int				count;
    int				i;
    t_texture_node	*node;
    t_texture_node	*previous;

    if (!(*textures = (t_textures*)malloc(sizeof(t_textures))))
        error_doom("can't malloc t_textures");
    if (!read(fd, &count, sizeof(count)))
        error_doom("can't read textures count");
    previous = NULL;
    i = 0;
    while (i < count)
    {
        read_texture_node_from_file(fd, &node);
        if (previous)
            previous->next = node;
        else
            (*textures)->first = node;
        previous = node;
        i++;
    }
}

void	write_textures_to_file(int fd, t_textures *textures)
{
    int				count;
    t_texture_node	*node;

    count = 0;
    node = textures->first;
    while (1)
    {
        if (!node)
            break;
        count++;
        node = node->next;
    }
    if (write(fd, &count, sizeof(count)) < 0)
        error_doom("can't write textures count");
    count = 0;
    node = textures->first;
    while (1)
    {
        if (!node)
            break;
        write_texture_node_to_file(fd, node);
        node = node->next;
        count++;
    }
}

void	read_texture_node_from_file(int fd, t_texture_node **texture_node)
{
    t_SDL_Surface_info	info;
    void				*pixels;

    if (!(*texture_node = (t_texture_node*)malloc(sizeof(texture_node))))
        error_doom("can't malloc t_texture_node");
    (*texture_node)->next = NULL;
    if (!read(fd, &info.w, sizeof(info.w)))
        error_doom("can't read info.w");
    if (!read(fd, &info.h, sizeof(info.h)))
        error_doom("can't read info.h");
    if (!read(fd, &info.depth, sizeof(info.depth)))
        error_doom("can't read info.depth");
    if (!read(fd, &info.pitch, sizeof(info.pitch)))
        error_doom("can't read info.pitch");
    if (!read(fd, &info.Rmask, sizeof(info.Rmask)))
        error_doom("can't read info.Rmask");
    if (!read(fd, &info.Gmask, sizeof(info.Gmask)))
        error_doom("can't read info.Gmask");
    if (!read(fd, &info.Bmask, sizeof(info.Bmask)))
        error_doom("can't read info.Bmask");
    if (!read(fd, &info.Amask, sizeof(info.Amask)))
        error_doom("can't read info.Amask");
    if (!(pixels = malloc(info.depth / 8 * info.w * info.h)))
        error_doom("can't malloc pixels");
    if (read(fd, pixels, info.depth / 8 * info.w * info.h) <= 0)
        error_doom("can't read pixels");
    if (!((*texture_node)->texture = SDL_CreateRGBSurfaceFrom(pixels, info.w,
            info.h, info.depth, info.pitch, info.Rmask, info.Gmask, info.Bmask,
            info.Amask)))
        error_doom("sdl couldn't create surface");
    read_str_from_file(fd, (char**)&(*texture_node)->texture->userdata);
}

void	write_texture_node_to_file(int fd, t_texture_node *texture_node)
{
    SDL_Surface			*texture;
    SDL_PixelFormat		format;
    
    texture = texture_node->texture;
    format = *(texture->format);
    if (write(fd, &(texture->w), sizeof(texture->w)) <= 0)
        error_doom("couldn't write texture w");
    if (write(fd, &(texture->h), sizeof(texture->h)) <= 0)
        error_doom("couldn't write texture h");
    if (write(fd, &(format.BitsPerPixel), sizeof(format.BitsPerPixel)) <= 0)
        error_doom("couldn't write texture BitsPerPixel");
    if (write(fd, &(texture->pitch), sizeof(texture->pitch)) <= 0)
        error_doom("couldn't write texture pitch");
    if (write(fd, &(format.Rmask), sizeof(format.Rmask)) <= 0)
        error_doom("couldn't write texture Rmask");
    if (write(fd, &(format.Gmask), sizeof(format.Gmask)) <= 0)
        error_doom("couldn't write texture Gmask");
    if (write(fd, &(format.Bmask), sizeof(format.Bmask)) <= 0)
        error_doom("couldn't write texture Bmask");
    if (write(fd, &(format.Amask), sizeof(format.Amask)) <= 0)
        error_doom("couldn't write texture Amask");
    if (write(fd, texture->pixels,
            format.BytesPerPixel * texture->w * texture->h) <= 0)
        error_doom("couldn't write pixels");
    write_str_to_file(fd, texture->userdata);
}

void	find_texture_from_file(int fd, t_textures *textures, SDL_Surface **surface)
{
    char	*name;

    read_str_from_file(fd, &name);
    find_texture_by_name(textures, name, surface);
    free(name);
}
