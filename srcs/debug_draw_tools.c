#include "doom.h"

void		debug_draw_player(SDL_Surface *surface, t_player *p)
{
	t_coords	copy;
	t_vector	v;
	t_segment	s;

	copy.x = p->pos.x * DEBUG_ZOOM + DEBUG_W_H;
	copy.y = DEBUG_H_H - p->pos.y * DEBUG_ZOOM;
	draw_circle_filled(surface, copy, 3, DEBUG_PLAYER_COLOR);

    v = create_vector(
    		cos(p->heading - ft_degtorad(HALF_FOV)),
    		sin(p->heading - ft_degtorad(HALF_FOV)));
    s = get_segment_from_vector(&v);
    move_segment_at(&s, copy.x, copy.y);
    change_segment_length(&s, HORIZON * DEBUG_ZOOM);
	draw_segment(surface, s, DEBUG_PLAYER_COLOR);

    v = create_vector(
    		cos(p->heading + ft_degtorad(HALF_FOV)),
    		sin(p->heading + ft_degtorad(HALF_FOV)));
    s = get_segment_from_vector(&v);
    move_segment_at(&s, copy.x, copy.y);
    change_segment_length(&s, HORIZON * DEBUG_ZOOM);
    draw_segment(surface, s, DEBUG_PLAYER_COLOR);
}

void		debug_draw_grid(SDL_Surface *surface)
{
	Uint32	x;
	Uint32	y;
	Uint32	debug_grid_step;
	t_segment to_draw;

	y = 0;
	debug_grid_step = DEBUG_GRID_STEP;
	while (y < DEBUG_H)
	{
		x = 0;
		while (x < DEBUG_W)
		{
			to_draw = create_segment(x, 0, x, DEBUG_H);
            draw_segment(surface,
            		to_draw, GRID_COLOR);
			x += debug_grid_step;
		}
		to_draw = create_segment(0, y, DEBUG_W, y);
		draw_segment(surface, to_draw, GRID_COLOR);
		y += debug_grid_step;
	}
	to_draw = create_segment(0, DEBUG_H_H, DEBUG_W, DEBUG_H_H);
	draw_segment(surface,
			to_draw, ABS_ORD_COLOR);
	to_draw = create_segment(DEBUG_W_H, 0, DEBUG_W_H, DEBUG_H);
	draw_segment(surface,
			to_draw, ABS_ORD_COLOR);
}

void		debug_draw_walls(SDL_Surface *surface, t_segment *s, Uint32 cnt)
{
	Uint32	i;
	t_segment s2;

	i = 0;
	while (i < cnt)
	{
		s2.x1 = DEBUG_W_H + s[i].x1 * DEBUG_ZOOM;
		s2.y1 = DEBUG_H_H - s[i].y1 * DEBUG_ZOOM;
		s2.x2 = DEBUG_W_H + s[i].x2 * DEBUG_ZOOM;
		s2.y2 = DEBUG_H_H - s[i].y2 * DEBUG_ZOOM;
		draw_segment(surface, s2, DEBUG_WALL_COLOR);
		i++;
	}
}