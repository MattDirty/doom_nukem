#ifndef DOOMNUKEM_IN_WHICH_SECTOR_H
# define DOOMNUKEM_IN_WHICH_SECTOR_H

# include "sectors.h"

int         is_in_sector(t_coords pos, t_sector *sector);
t_sector    *in_which_sector(t_coords pos, t_sectors *sectors);

#endif
