#ifndef DOOMNUKEM_SECTORS_H
#define DOOMNUKEM_SECTORS_H

#include "walls.h"

typedef	struct			s_sector
{
    t_walls			*walls;
}						t_sector;

typedef struct			s_sectors
{
    int					count;
    t_sector			 *items;
}						t_sectors;


#endif
