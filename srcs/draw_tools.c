#include "doom.h"

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