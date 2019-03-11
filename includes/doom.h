#ifndef DOOMNUKEM_DOOM_H
# define DOOMNUKEM_DOOM_H

# include "SDL.h"
# include "libft.h"

# include <stdio.h>
# include <math.h>
# include <stdlib.h>
# include "SDL.h"

# define	DEBUG_W 800
# define	DEBUG_H	640
# define	DEBUG_W_H DEBUG_W / 2
# define	DEBUG_H_H DEBUG_H / 2
# define	DEBUG_GRID_STEP 40
# define	DEBUG_ZOOM 20

# define WIN_W 800
# define WIN_H 600
# define HALF_W WIN_W / 2
# define HALF_H WIN_H / 2

# define FOV 60.0
# define HORIZON 10
# define DECR_ANG ft_degtorad(FOV / (double)WIN_W)
# define RATIO HALF_W / tan(ft_degtorad(FOV / 2))

# define SKYBLUE 0xFF0EC0EE
# define BROWN 0xFF452209
# define BLACK 0xFF000000
# define WHITE 0xFFFFFFFF

# define NORTH ft_degtorad(90)
# define SOUTH ft_degtorad(270)
# define WEST ft_degtorad(180)
# define EAST 0
# define CIRCLE ft_degtorad(360)

# define ROT ft_degtorad(5)
# define MOUSE_SENSI 0.1

typedef struct	s_coords
{
	double	x;
	double	y;
}				t_coords;

typedef struct	s_segment
{
	double	x1;
	double	y1;
	double	x2;
	double	y2;
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

typedef struct			s_player
{
        t_coords	pos;
        double		vis;
        double		height;
}						t_player;

typedef struct			s_ray
{
        double			ang;
        double			tan;
        t_coords		hit;
        double			dist;
        double			length;
}						t_ray;

typedef struct          s_env
{
		SDL_Window		*win;
        SDL_Renderer    *render;
        SDL_Renderer	*debug_r;
        SDL_Texture		*text;
        SDL_Surface		*surf;
        t_segment		*walls;
        Uint32			seg_count;
        int				col;
        int                             start;
        int                             end;
        Uint32                  color;
        t_player                *p;
        t_ray                   *r;
}                                       t_env;

enum e_bool	get_line_intersection(t_segment *a, t_segment *b, t_coords *inters);

t_vector	create_vector(double x, double y);
t_vector	create_vector_at(double x, double y, double pos_x, double pos_y);
void		move_vector_at(t_vector *vector, double x, double y);
void		print_vector(t_vector *vector, char *str);

t_segment	create_segment(double x1, double y1, double x2, double y2);
t_segment	get_segment_from_vector(t_vector *vector);
void		move_segment_at(t_segment *s, double x, double y);
void		change_segment_length(t_segment *s, double length);
enum e_bool segments_intersect(t_segment *a, t_segment *b,t_coords *inters);
void		print_segment(t_segment *segment, char *str);

void		error_doom(char *err);
int			quit_doom(t_env *e);
void		init_doom(t_env *e);

void		loop_doom(t_env *e);

void		raycasting(t_env *e);

Uint32		get_pixel(SDL_Surface *s, int x, int y);
void		put_pixel(SDL_Surface *s, int x, int y, Uint32 color);
void        print_surface(SDL_Renderer *r, SDL_Surface *surf);


void		draw(t_env *e);
void		draw_circle(SDL_Renderer *renderer, t_coords center, int r);
void        draw_segment(SDL_Renderer *r, t_segment *s);

SDL_Renderer	*debug_init(t_segment *segments, Uint32 s_count, t_player *p);
void		debug_draw_walls(SDL_Renderer *r, t_segment *s, Uint32 cnt);
void		debug_draw_grid(SDL_Renderer *renderer);
void		debug_draw_player(SDL_Renderer *r, t_player *p);
void		debug_draw(SDL_Renderer *r, t_segment *s, Uint32 s_cnt, t_player *p);


#endif
