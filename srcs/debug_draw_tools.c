#include "doom.h"

void		debug_draw_player(SDL_Renderer *r, t_player *p)
{
	t_coords	copy;
	t_vector	v;
	t_segment	s;

	copy.x = p->pos.x * DEBUG_ZOOM + DEBUG_W_H;
	copy.y = DEBUG_H_H - p->pos.y * DEBUG_ZOOM;
	SDL_SetRenderDrawColor(r, 0, 255, 255, 255);
	draw_circle(r, copy, 3);
	draw_circle(r, copy, 2);
	SDL_SetRenderDrawColor(r, 255, 255, 255, 255);
	draw_circle(r, copy, 1);
    SDL_SetRenderDrawColor(r, 0, 255, 255, 255);
    v = create_vector(cos(p->vis - ft_degtorad(FOV/2)), sin(p->vis - ft_degtorad(FOV/2)));
    s = get_segment_from_vector(&v);
    move_segment_at(&s, DEBUG_W_H + p->pos.x * DEBUG_ZOOM, DEBUG_H_H - p->pos.y * DEBUG_ZOOM);
    change_segment_length(&s, HORIZON * DEBUG_ZOOM);
    draw_segment(r, &s);
    v = create_vector(cos(p->vis + ft_degtorad(FOV/2)), sin(p->vis + ft_degtorad(FOV/2)));
    s = get_segment_from_vector(&v);
    move_segment_at(&s, DEBUG_W_H + p->pos.x * DEBUG_ZOOM, DEBUG_H_H - p->pos.y * DEBUG_ZOOM);
    change_segment_length(&s, HORIZON * DEBUG_ZOOM);
    draw_segment(r, &s);
}

void		debug_draw_grid(SDL_Renderer *renderer)
{
	Uint32	x;
	Uint32	y;
	Uint32	debug_grid_step = DEBUG_GRID_STEP;

	y = 0;
	SDL_SetRenderDrawColor(renderer, 40, 40, 0, 255);
	while (y < DEBUG_H)
	{
		x = 0;
		while (x < DEBUG_W)
		{
			SDL_RenderDrawLine(renderer, x, 0, x, DEBUG_H);
			x += debug_grid_step;
		}
		SDL_RenderDrawLine(renderer, 0, y, DEBUG_W, y);
		y += debug_grid_step;
	}
	SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
	SDL_RenderDrawLine(renderer, 0, DEBUG_H_H, DEBUG_W, DEBUG_H_H);
	SDL_RenderDrawLine(renderer, DEBUG_W_H, 0, DEBUG_W_H, DEBUG_H);
}

void		debug_draw_walls(SDL_Renderer *r, t_segment *s, Uint32 cnt)
{
	Uint32	i;
	t_segment s2;

	SDL_SetRenderDrawColor(r, 255, 0, 0, 255);
	i = 0;
	while (i < cnt)
	{
		s2.x1 = DEBUG_W_H + s[i].x1 * DEBUG_ZOOM;
		s2.y1 = DEBUG_H_H - s[i].y1 * DEBUG_ZOOM;
		s2.x2 = DEBUG_W_H + s[i].x2 * DEBUG_ZOOM;
		s2.y2 = DEBUG_H_H - s[i].y2 * DEBUG_ZOOM;
		draw_segment(r, &s2);
		i++;
	}
}