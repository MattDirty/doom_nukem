#include "doom.h"
//
//void		draw_segment(SDL_Surface *surface, t_segment *segment, int color)
//{
//
//}

void		draw_segment(SDL_Renderer *r, t_segment *s)
{
    SDL_RenderDrawLine(r, s->x1, s->y1, s->x2, s->y2);
}

void	draw_circle(SDL_Renderer *renderer, t_coords center, int r)
{
	int	x;
	int	y;
	int	tx;
	int	ty;
	int	err;

	x = r - 1;
	y = 0;
	tx = 0;
	ty = 0;
	err = tx - (r << 1);
	while (x >= y)
	{
		SDL_RenderDrawPoint(renderer, center.x + x, center.y - y);
		SDL_RenderDrawPoint(renderer, center.x + x, center.y + y);
		SDL_RenderDrawPoint(renderer, center.x - x, center.y - y);
		SDL_RenderDrawPoint(renderer, center.x - x, center.y + y);
		SDL_RenderDrawPoint(renderer, center.x + y, center.y - x);
		SDL_RenderDrawPoint(renderer, center.x + y, center.y + x);
		SDL_RenderDrawPoint(renderer, center.x - y, center.y - x);
		SDL_RenderDrawPoint(renderer, center.x - y, center.y + x);
		if (err <= 0)
		{
			y++;
			err += ty;
			ty += 2;
		}
		if (err > 0)
		{
			x--;
			tx += 2;
			err += tx - (r << 1);
		}
	}
}