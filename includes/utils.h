#ifndef UTILS_H
# define UTILS_H

# include <time.h>
# include <SDL.h>
# include "e_bool.h"

# define COS_PI_FOURTH 0.7071
# define COS_PI_EIGTH 0.9239

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

typedef struct	s_u_range
{
	Uint32		start;
	Uint32		end;
}				t_u_range;

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

typedef struct	s_rect
{
	t_i_coords	pos;
	int			width;
	int			height;
}				t_rect;

t_vector	create_vector(double x, double y);
t_vector	get_vector_from_segment(t_segment *segment);
void		print_vector(t_vector *vector, char *str);
void        scalar_multiply(t_vector *vector, double scalar);
void		normalize_vector(t_vector *vector);
void        add_vector_to_vector(t_vector *vector, t_vector vector2);
void        rotate_vector(t_vector *vector, double rad);
void		change_vector_magnitude(t_vector *vector, double new_magnitude);
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
enum e_bool segments_intersect(t_segment *a, t_segment *b, t_coords *inters);
enum e_bool	segments_share_node(t_segment *s1, t_segment *s2);

double      delta_ms(struct timespec start, struct timespec end);
double      get_distance_between_points(double x1, double y1, double x2, double y2);

void		read_segment_from_file(int fd, t_segment *segment);
void		write_segment_to_file(int fd, t_segment *segment);

t_rect      create_rect(int x, int y, int width, int height);
void        draw_rect(SDL_Surface *surface, t_rect *rect, Uint32 color);
void        fill_rect(SDL_Surface *surface, t_rect *rect, Uint32 color, enum e_bool alpha);
enum e_bool is_in_rect(t_rect *rect, int x, int y);

#endif
