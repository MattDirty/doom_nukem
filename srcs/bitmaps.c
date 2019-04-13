#include <fcntl.h>
#include <unistd.h>
#include "bitmaps.h"
#include "doom.h"

t_SDL_Surface_info		read_header(int fd, int *pixels_size)
{
    t_SDL_Surface_info	info;
    char				buffer[124];
    int					pixels_offset;

    if (read(fd, &buffer, 2) <= 0 || buffer[0] != 'B' || buffer[1] != 'M')
        error_doom("nope");
    if (read(fd, pixels_size, sizeof(int)) <= 0)
        error_doom("mistaken bitmap assery");
    if (read(fd, buffer, 4) <= 0)
        error_doom("reserved cock");
    if (read(fd, &pixels_offset, sizeof(int)) <= 0)
        error_doom("pixels offet");
    if (pixels_offset != 138 || read(fd, buffer, pixels_offset - 14) <= 0)
        error_doom("Can't read a BITMAPV5HEADER.");
    *pixels_size -= pixels_offset;
    info.h = *((unsigned int*)&buffer[4]);
    info.w = *((unsigned int*)&buffer[8]);
    info.depth = *((unsigned int*)&buffer[20]) / info.h / info.w * 8;
    info.pitch = info.w * info.depth / 8;
    info.Rmask = *((unsigned int*)&buffer[40]);
    info.Gmask = *((unsigned int*)&buffer[44]);
    info.Bmask = *((unsigned int*)&buffer[48]);
    info.Amask = *((unsigned int*)&buffer[52]);
    return (info);
}

static char				*read_pixels(int fd, int pixel_size)
{
    char				*pixels;

    if (!(pixels = malloc(pixel_size)))
        error_doom("buy some more ram plz");
    if (read(fd, pixels, pixel_size) <= 0)
        error_doom("yeah well too bad");
    return (pixels);
}

SDL_Surface				*load_bmp(char* path)
{
    int					fd;
    t_SDL_Surface_info	info;
    int					pixels_size;
    SDL_Surface			*ret;
    char				*pixels;

    fd = open(path, O_RDONLY);
    info = read_header(fd, &pixels_size);
    pixels = read_pixels(fd, pixels_size);
    close(fd);
    ret = SDL_CreateRGBSurfaceFrom(pixels, info.w, info.h, info.depth,
            info.pitch, info.Rmask, info.Gmask, info.Bmask, info.Amask);
    if (ret == NULL)
        error_doom("I've done all I could but it wasn't enough");
    free(pixels);
    return (ret);
}
