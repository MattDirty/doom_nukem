#ifndef DOOM_H
# define DOOM_H

# include "SDL.h"
# include "libft.h"

# include <stdio.h>
# include <math.h>
# include <stdlib.h>

# define	DEBUG_W 800
# define	DEBUG_H	640
# define	DEBUG_W_H (DEBUG_W / 2)
# define	DEBUG_H_H (DEBUG_H / 2)
# define	DEBUG_GRID_STEP 40
# define	DEBUG_ZOOM 20
# define 	GRID_COLOR 0xFFB8D34E
# define	ABS_ORD_COLOR 0xFFE2EA4F
# define	DEBUG_WALL_COLOR 0xFFFF0000
# define	DEBUG_PLAYER_COLOR 0XFF4FE4EA


# define WIN_W 800
# define WIN_H 640
# define HALF_W ((double)WIN_W / 2)
# define HALF_H ((double)WIN_H / 2)

# define FOV 90.0
# define HALF_FOV (FOV / 2)
# define HORIZON 10
# define TAN_HALF_FOV (tan(ft_degtorad(HALF_FOV)))
# define RATIO (HALF_W / TAN_HALF_FOV)

# define SKYBLUE 0xFF0EC0EE
# define BROWN 0xFF452209
# define BLACK 0xFF000000
# define WHITE 0xFFFFFFFF

# define NORTH (ft_degtorad(90))
# define SOUTH (ft_degtorad(270))
# define WEST (ft_degtorad(180))
# define EAST 0
# define CIRCLE (ft_degtorad(360))

# define ROT_90 NORTH
# define PLAYER_THICKNESS 1.0
# define ROT (ft_degtorad(5))
# define MOUSE_SENSI 0.01
# define RUN 0.001
# define STRAFE (RUN / 2)

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

typedef struct	s_vector
{
    double x;
    double y;
}				t_vector;

enum			e_bool
{
	t_false = 0,
	t_true = 1
};

typedef struct			s_player
{
        t_coords	pos;
        double		heading;
        double		height;
}						t_player;

typedef struct			s_sdl
{
	SDL_Window			*window;
	SDL_Renderer		*renderer;
	SDL_Texture			*texture;
	SDL_Surface			*surface;
}						t_sdl;

typedef	struct			s_sector
{
		t_segment		*walls;
		int             wall_id; //debug
		Uint32			seg_count;
}						t_sector;

typedef struct          s_env
{
		t_sdl			debug;
		SDL_Window		*win;
        SDL_Renderer    *render;
        SDL_Texture		*text;
        SDL_Surface		*surf;
        int				col;
		Uint32          color;
        t_player        *p;
        t_sector		*sector;
}                                       t_env;

t_vector	create_vector(double x, double y);
t_vector	get_vector_from_segment(t_segment *segment);
void		print_vector(t_vector *vector, char *str);
void        scalar_multiply(t_vector *vector, double scalar);
t_segment	create_segment_from_position_and_vector(
		double x,
		double y,
		t_vector *v);

t_segment	create_segment(double x1, double y1, double x2, double y2);
t_segment	get_segment_from_vector(t_vector *vector);
void		move_segment_at(t_segment *segment, double x, double y);
void		change_segment_length(t_segment *s, double length);
void		print_segment(t_segment *segment, char *str);

void		error_doom(char *err);
int			quit_doom(t_env *e);
void		init_doom(t_env *e);

void		loop_doom(t_env *e);

double		check_collision(t_sector *sector, t_player *p, t_vector *vector);
void		raycasting(t_env *e);

void		move(t_player *p, t_sector *sector, const Uint8 *state);

Uint32		get_pixel(SDL_Surface *s, int x, int y);

void		put_pixel(SDL_Surface *s, int x, int y, Uint32 color);
void		draw_circle(SDL_Surface *surface, t_coords center, int r, Uint32 color);
void		draw_circle_filled(SDL_Surface *surface, t_coords center, int r, Uint32 color);
void        draw_segment(SDL_Surface *surface, t_segment segment, Uint32 color);

void        print_surface(SDL_Renderer *r, SDL_Surface *surf);


void		draw(t_env *e, double ray_angle, double distance);

t_sdl		debug_init();
void		debug_draw_walls(SDL_Surface *surface, t_segment *s, Uint32 cnt);
void		debug_draw_grid(SDL_Surface *surface);
void		debug_draw_player(SDL_Surface *surface, t_player *p);
void		debug_draw(t_sdl *debug, t_segment *s, Uint32 s_cnt, t_player *p);

#endif
