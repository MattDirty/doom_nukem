#ifndef SECTORS_H
# define SECTORS_H

# include "walls.h"

typedef	struct			s_sector
{
    t_walls			    *walls;
    SDL_Surface         *floor;
    SDL_Surface         *ceil;
    enum e_bool         open_sky;
}						t_sector;

typedef struct			s_sectors
{
    int					count;
    t_sector			 *items;
}						t_sectors;


#endif
