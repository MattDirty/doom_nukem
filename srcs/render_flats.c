/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_flats.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfatton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/20 09:43:52 by lfatton           #+#    #+#             */
/*   Updated: 2019/04/20 09:43:53 by lfatton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "collision.h"
#include "doom.h"
#include "default.h"
#include "render.h"
#include "render_blackhole.h"
#include "surface_manipulation.h"
#include <math.h>

void	draw_flat(t_render *render, t_collision *collision, t_u_range range,
			SDL_Surface *texture)
{
	double		pixel_dist;
	double		weight;
	t_i_coords	incr;
	Uint32		color_text;
	Uint32		renderer_y;

	renderer_y = range.start;
	while (renderer_y < range.end)
	{
		pixel_dist = render->win_h / fabs(render->vision_height - renderer_y);
		weight = pixel_dist / collision->distance;
		incr.x = (Uint32)((weight * collision->inters.x + (BLACK_MAGIC - weight)
			* render->p_pos.x) * texture->w) % texture->w;
		incr.y = (Uint32)((weight * collision->inters.y + (BLACK_MAGIC - weight)
			* render->p_pos.y) * texture->h) % texture->h;
		color_text = get_pixel(texture, incr.x, incr.y, e_true);
		put_pixel_blackhole(render->bandaid, render->x, renderer_y, color_text);
		if (render->lights)
			put_pixel_blackhole(render->bandaid, render->x, renderer_y,
				render->light_value);
		renderer_y++;
	}
}

void	draw_ceil(t_render *render, t_collision *collision, t_u_range range,
			t_sector *current_sector)
{
	if (current_sector->open_sky)
	{
		skybox(render, range);
		return ;
	}
	draw_flat(render, collision, range, current_sector->ceil);
}
