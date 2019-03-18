#ifndef DOOM_H
# define DOOM_H

# include "SDL.h"
# include "libft.h"

# include "e_bool.h"
# include "utils.h"
# include "player.h"
# include "weapon.h"

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

# define WIN_W 1600
# define WIN_H 1280
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
# define ROT_X 0.0005
# define ROT_Y 1
# define MOUSE_SENSI 0.000001

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

void        ui_draw(t_sdl *sdl);
void        draw_crosshair(SDL_Surface *surface, Uint32 color);

t_sdl		debug_init();
void		debug_draw_walls(SDL_Surface *surface, t_walls *walls);
void		debug_draw_grid(SDL_Surface *surface);
void		debug_draw_player(SDL_Surface *surface, t_player *p);
void		debug_draw(t_sdl *debug, t_map *map, t_player *p);

double      delta_ms(struct timespec start, struct timespec end);

#endif
