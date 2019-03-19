#ifndef DOOMNUKEM_STRUCT_SDL_H
# define DOOMNUKEM_STRUCT_SDL_H

# include "SDL.h"

typedef struct			s_sdl
{
    SDL_Window			*window;
    SDL_Renderer		*renderer;
    SDL_Texture			*texture;
    SDL_Surface			*surface;
}						t_sdl;

#endif
