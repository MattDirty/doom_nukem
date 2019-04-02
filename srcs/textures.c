#include <unistd.h>
#include <errno.h>

#include "SDL.h"
#include "libft.h"

#include "textures.h"
#include "serialisation.h"

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

int	find_texture_by_name(
        t_textures *textures,
        char *name,
        SDL_Surface **texture)
{
    t_texture_node	*node;

    node = textures->first;
    if (!node)
        return (-1);
    while (node)
    {
        if (ft_strcmp(node->texture->userdata, name) == 0)
        {
            *texture = node->texture;
            return (0);
        }
        node = node->next;
    }
    return (-2);
}

int	add_bitmap_file_to_textures(
        t_textures *textures,
        char *path)
{
    SDL_Surface		*texture;
    t_texture_node	*node;

    texture = SDL_LoadBMP(path);
    if (!texture)
        return (-1);
    if (!(node = (t_texture_node*)malloc(sizeof(t_texture_node))))
        return (-2);
    texture->userdata = path;
    node->texture = texture;
    node->next = NULL;
    add_texture(textures, node);
    return (0);
}

int	read_textures_from_file(int fd, t_textures **textures)
{
    int				count;
    int				i;
    t_texture_node	*node;
    t_texture_node	*previous;

    if (!(*textures = (t_textures*)malloc(sizeof(t_textures))))
        return (-1);
    if (!read(fd, &count, sizeof(count)))
    {
        free(*textures);
        return (-2);
    }
    previous = NULL;
    i = 0;
    while (i < count)
    {
        if (read_texture_node_from_file(fd, &node))
            return (-3);
        if (previous)
            previous->next = node;
        else
            (*textures)->first = node;
        previous = node;
        i++;
    }
    return (0);
}

int	write_textures_to_file(int fd, t_textures *textures)
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
    if ((write(fd, &count, sizeof(count))) < 0)
        return (-1);
    count = 0;
    node = textures->first;
    while (1)
    {
        if (!node)
            break;
        if (write_texture_node_to_file(fd, node) < 0)
            return (-2);
        node = node->next;
        count++;
    }
    return (0);
}

int	read_texture_node_from_file(int fd, t_texture_node **texture_node)
{
    t_SDL_Surface_info	info;
    void				*pixels;

    if (!(*texture_node = (t_texture_node*)malloc(sizeof(texture_node))))
        return (-1);
    (*texture_node)->next = NULL;
    if (!read(fd, &info.w, sizeof(info.w)))
        return (-2);
    if (!read(fd, &info.h, sizeof(info.h)))
        return (-3);
    if (!read(fd, &info.depth, sizeof(info.depth)))
        return (-4);
    if (!read(fd, &info.pitch, sizeof(info.pitch)))
        return (-5);
    if (!read(fd, &info.Rmask, sizeof(info.Rmask)))
        return (-6);
    if (!read(fd, &info.Gmask, sizeof(info.Gmask)))
        return (-7);
    if (!read(fd, &info.Bmask, sizeof(info.Bmask)))
        return (-8);
    if (!read(fd, &info.Amask, sizeof(info.Amask)))
        return (-9);
    if (!(pixels = malloc(info.depth / 8 * info.w * info.h)))
        return (-10);
    if (read(fd, pixels, info.depth / 8 * info.w * info.h) <= 0)
        return (-11);
    (*texture_node)->texture = SDL_CreateRGBSurfaceFrom(
            pixels,
            info.w,
            info.h,
            info.depth,
            info.pitch,
            info.Rmask,
            info.Gmask,
            info.Bmask,
            info.Amask);
    if (!(*texture_node)->texture)
        return (-12);
    if (read_str_from_file(
            fd,
            (char**)&(*texture_node)->texture->userdata) < 0)
        return (-13);
    return (0);
}

int	write_texture_node_to_file(int fd, t_texture_node *texture_node)
{
    SDL_Surface			*texture;
    SDL_PixelFormat		format;
    
    texture = texture_node->texture;
    format = *(texture->format);
    if (write(fd, &(texture->w), sizeof(texture->w)) <= 0)
        return (-1);
    if (write(fd, &(texture->h), sizeof(texture->h)) <= 0)
        return (-2);
    if (write(fd, &(format.BitsPerPixel), sizeof(format.BitsPerPixel)) <= 0)
        return (-4);
    if (write(fd, &(texture->pitch), sizeof(texture->pitch)) <= 0)
        return (-5);
    if (write(fd, &(format.Rmask), sizeof(format.Rmask)) <= 0)
        return (-6);
    if (write(fd, &(format.Gmask), sizeof(format.Gmask)) <= 0)
        return (-7);
    if (write(fd, &(format.Bmask), sizeof(format.Bmask)) <= 0)
        return (-8);
    if (write(fd, &(format.Amask), sizeof(format.Amask)) <= 0)
        return (-9);
    if (write(
            fd,
            texture->pixels,
            format.BytesPerPixel * texture->w * texture->h) <= 0)
        return (-10);
    if (write_str_to_file(fd, texture->userdata) < 0)
        return (-11);
    return (0);
}

int	find_texture_from_file(int fd, t_textures *textures, SDL_Surface **surface)
{
    char	*name;

    if (read_str_from_file(fd, &name) < 0)
        return (-1);
    if (find_texture_by_name(textures, name, surface) < 0)
        return (-2);
    free(name);
    return (0);
}
