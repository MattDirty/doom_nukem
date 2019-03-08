#ifndef DOOMNUKEM_DOOM_H
# define DOOMNUKEM_DOOM_H

# include <stdio.h>
# include <math.h>

typedef struct	s_coords
{
	double	x;
	double	y;
}				t_coords;

typedef struct	s_segment
{
	t_coords	start;
	t_coords	end;
}				t_segment;

typedef struct	s_vector
{
	t_coords	direction;
	t_coords	pos;
}				t_vector;

enum			e_bool
{
	t_false = 0,
	t_true = 1
};

t_vector	create_vector_at(double x, double y, double pos_x, double pos_y);
void		move_vector_at(t_vector *vector, double x, double y);
void		print_vector(t_vector *vector, char *str);
t_segment	create_segment(double x1, double y1, double x2, double y2);
t_segment	get_segment_from_vector(t_vector *vector);
void		change_segment_length(t_segment *s, double length);
void		print_segment(t_segment *segment, char *str);

#endif
