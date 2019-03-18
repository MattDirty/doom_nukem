#ifndef DOOM_H
# define DOOM_H

# include "SDL.h"
# include "libft.h"

# include <time.h>
# include <stdio.h>
# include <math.h>
# include <stdlib.h>

# define DEBUG_W 800
# define DEBUG_H 640
# define DEBUG_W_H (DEBUG_W / 2)
# define DEBUG_H_H (DEBUG_H / 2)
# define DEBUG_GRID_STEP 40
# define DEBUG_ZOOM 20

# define GRID_COLOR 0xFF111111
# define ABS_ORD_COLOR 0xFFE2EAFF
# define DEBUG_WALL_COLOR 0xFFFF0000
# define DEBUG_PLAYER_COLOR 0xFF4FE4EA

# define CROSSHAIR_COLOR 0xE400FF00

# define FPS_MAX 60

# define WIN_W 800
# define WIN_H 640
# define HALF_W ((double)WIN_W / 2)
# define HALF_H ((double)WIN_H / 2)

# define PIXEL_UNIT 225
# define FOV 90.0
# define HALF_FOV (FOV / 2)
# define HORIZON 25
# define TAN_HALF_FOV (tan(ft_degtorad(HALF_FOV)))
# define RATIO (HALF_W / TAN_HALF_FOV)

# define MASK_ALPHA 0xFF000000
# define MASK_RED 0x00FF0000
# define MASK_GREEN 0x0000FF00
# define MASK_BLUE 0x000000FF

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
# define RUN 0.001

# define PLAYER_THICKNESS 0.25
# define ROT_X 0.1
# define ROT_Y 1
# define MOUSE_SENSI 0.005

typedef struct	s_coords
{
	double	x;
	double	y;
}				t_coords;

typedef struct  s_color
{
    Uint8       alpha;
    Uint8       red;
    Uint8       green;
    Uint8       blue;
}               t_color;

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
        double		vision_height;
        t_vector    speed;
        SDL_Surface *weapon;
}						t_player;

typedef struct			s_sdl
{
	SDL_Window			*window;
	SDL_Renderer		*renderer;
	SDL_Texture			*texture;
	SDL_Surface			*surface;
}						t_sdl;

typedef struct			s_wall
{
	t_segment			segment;
	double				height; //debug
	SDL_Surface			*texture;
}						t_wall;

typedef struct          s_collision
{
	double              distance;
	t_coords            inters;
	t_wall				*wall;
}                       t_collision;

typedef struct			s_walls
{
	int					count;
	t_wall				 *items;
}						t_walls;

typedef	struct			s_sector
{
		t_walls			*walls;
}						t_sector;

typedef struct			s_sectors
{
	int					count;
	t_sector			 *items;
}						t_sectors;

typedef struct			s_map
{
	t_sectors			*sectors;
}						t_map;

typedef struct          s_env
{
		t_sdl			debug;
		enum e_bool     debug_mode;
        t_player        *p;
        t_sdl           *doom;
}                       t_env;

void        print_t_color(t_color color);
t_color 	int_to_t_color(Uint32 color);
Uint32	    t_color_to_int(t_color color);
t_color 	create_argb(Uint8 alpha, Uint8 red, Uint8 green, Uint8 blue);

double  get_distance_between_points(double x1, double y1, double x2, double y2);

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

void		error_doom(char *err);
int			quit_doom(t_env *e);
void		init_doom(t_env *e);

void		loop_doom(t_env *e, t_map *map);

t_collision	check_collision(t_sector *sector, t_segment *seg);
void		raycasting(t_env *e, t_map *map);

void		move(t_player *p, t_map* map, const Uint8 *state, double time);
void        look_up_and_down(t_player *p, const Uint8 *state, double time);

Uint32		get_pixel(SDL_Surface *s, int x, int y, enum e_bool force_alpha);

void		put_pixel(SDL_Surface *s, int x, int y, Uint32 color);
void	    put_pixel_alpha(SDL_Surface *s, int x, int y, Uint32 color);

void		draw_circle(SDL_Surface *surface, t_coords center, int r, Uint32 color);
void		draw_circle_filled(SDL_Surface *surface, t_coords center, int r, Uint32 color);
void        draw_segment(SDL_Surface *surface, t_segment segment, Uint32 color);

void        print_surface(SDL_Renderer *r, SDL_Surface *surf);


void		draw(t_env *e, double ray_angle, t_collision collision, Uint32 renderer_x);

void        ui_draw(t_sdl *sdl, SDL_Surface *weapon);
void        draw_crosshair(SDL_Surface *surface, Uint32 color);

t_sdl		debug_init();
void		debug_draw_walls(SDL_Surface *surface, t_walls *walls);
void		debug_draw_grid(SDL_Surface *surface);
void		debug_draw_player(SDL_Surface *surface, t_player *p);
void		debug_draw(t_sdl *debug, t_map *map, t_player *p);

double      delta_ms(struct timespec start, struct timespec end);

#endif
