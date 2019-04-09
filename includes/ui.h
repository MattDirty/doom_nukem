#ifndef UI_H
# define UI_H

# include "SDL_ttf.h"
# include "struct_sdl.h"
# include "config.h"

typedef struct  s_font
{
    TTF_Font    *game_over;
    TTF_Font    *nightnday;
}               t_font;

void        ui_draw(t_sdl *sdl, t_config *op);

t_font      load_fonts(void);

#endif
