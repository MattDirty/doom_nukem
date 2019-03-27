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
        return (-1);
    }
    
    previous = NULL;

    i = 0;
    while (i < count)
    {
        if (read_texture_node_from_file(fd, &node))
            /* TODO #5:
             * Leaks memory, we need to parse the list and free shit
             * but I'm too lazy right now */
            return (-1);

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
            return (-1);

        node = node->next;
        count++;
    }

    return (0);
}

int	read_texture_node_from_file(int fd, t_texture_node **texture_node)
{
    int				width;
    int				height;
    int				pitch;
    void			*pixels;

    if (!(*texture_node = (t_texture_node*)malloc(sizeof(texture_node))))
        return (-1);
    
    (*texture_node)->next = NULL;

    if (!read(fd, &width, sizeof(width)))
        return (-2);
    if (!read(fd, &height, sizeof(height)))
        return (-3);
    if (!read(fd, &pitch, sizeof(pitch)))
        return (-4);

    if (!(pixels = malloc(sizeof(Uint32) * width * height)))
        return (-5);

    if (!read(fd, pixels, sizeof(Uint32) * width * height))
        return (-6);
    
    (*texture_node)->texture = SDL_CreateRGBSurfaceFrom(
            pixels,
            width,
            height,
            BITMAP_DEPTH,
            pitch,
            0xff000000,
            0x00ff0000,
            0x0000ff00,
            0x000000ff);
    read_str_from_file(fd, (char**)&(*texture_node)->texture->userdata);

    return (0);
}

int	write_texture_node_to_file(int fd, t_texture_node *texture_node)
{
    SDL_Surface		*texture;
    
    texture = texture_node->texture;

    if (write(fd, &(texture->w), sizeof(texture->w)) <= 0)
        return (-1);
    if (write(fd, &(texture->h), sizeof(texture->h)) <= 0)
        return (-2);
    if (write(fd, &(texture->pitch), sizeof(texture->pitch)) <= 0)
        return (-3);
    if (write(
            fd,
            texture->pixels,
            sizeof(Uint32) * texture->w * texture->h) <= 0)
        return (-4);
    if (write_str_to_file(fd, texture->userdata) < 0)
        return (-5);

    return (0);
}
