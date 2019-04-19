#ifndef DOOMNUKEM_IN_WHICH_SECTOR_H
# define DOOMNUKEM_IN_WHICH_SECTOR_H

# include "sectors.h"

int         is_in_sector(t_coords pos, t_sector *sector);
t_sector    *in_which_sector(t_coords pos, t_sectors *sectors);
//enum e_bool	line_through_segment_intersects_point(t_segment segment,
//		double x, double y);
void			rotate_segment_around_first_extremity(t_segment *segment,
		const double angle);
enum e_bool		line_through_segment_intersects_a_sector_vertex(
		t_segment segment, t_sector *sector);

#endif
