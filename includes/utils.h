#ifndef DOOMNUKEM_UTILS_H
# define DOOMNUKEM_UTILS_H

#include <time.h>

typedef struct	s_vector
{
    double x;
    double y;
}				t_vector;

typedef struct	s_coords
{
    double	x;
    double	y;
}				t_coords;

typedef struct  s_i_coords
{
    int     x;
    int     y;
}               t_i_coords;

typedef struct	s_segment
{
    double	x1;
    double	y1;
    double	x2;
    double	y2;
}				t_segment;

typedef struct	s_i_segment
{
    int	x1;
    int	y1;
    int	x2;
    int	y2;
}				t_i_segment;

t_vector	create_vector(double x, double y);
t_vector	get_vector_from_segment(t_segment *segment);
void		print_vector(t_vector *vector, char *str);
void        scalar_multiply(t_vector *vector, double scalar);
void        add_vector_to_vector(t_vector *vector, t_vector vector2);
void        rotate_vector(t_vector *vector, double rad);
double      dot_product(t_vector *vector1, t_vector *vector2);
double      get_vector_length(t_vector *vector);
double      get_rad_between_vectors(t_vector *vector1, t_vector *vector2);
t_segment	create_segment_from_position_and_vector(
        double x,
        double y,
        t_vector *v);

t_segment	create_segment(double x1, double y1, double x2, double y2);
t_segment	get_segment_from_vector(t_vector *vector);
double      get_segment_length(t_segment *segment);
void		move_segment_at(t_segment *segment, double x, double y);
void		change_segment_length(t_segment *s, double length);
void		print_segment(t_segment *segment, char *str);

double      delta_ms(struct timespec start, struct timespec end);

#endif