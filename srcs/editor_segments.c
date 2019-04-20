/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_segments.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfatton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/20 06:35:51 by lfatton           #+#    #+#             */
/*   Updated: 2019/04/20 06:35:53 by lfatton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"
#include "editor_panel_buttons.h"
#include "editor_mouse_clicks.h"
#include "ui.h"
#include "walls.h"
#include "editor_states.h"

void	split_wall(t_params params)
{
	t_btn_params	*btn_params;
	t_wall			*wall;
	t_sector		*sector;
	t_wall			*new_wall;

	btn_params = (t_btn_params *)params;
	wall = btn_params->ed->selected.wall;
	sector = find_wall_sector(btn_params->ed->map->sectors, wall);
	if (get_segment_length(&wall->segment) < 1 || sector->walls->count >= 15)
		return ;
	new_wall = create_wall_copy(wall);
	new_wall->segment.x1 += (new_wall->segment.x2 - new_wall->segment.x1) / 2;
	new_wall->segment.y1 += (new_wall->segment.y2 - new_wall->segment.y1) / 2;
	wall->segment.x2 = new_wall->segment.x1;
	wall->segment.y2 = new_wall->segment.y1;
	add_wall_to_sector(sector, new_wall);
	free_linked_walls_nodes(btn_params->ed->linked_walls);
	create_linked_walls_from_sectors(btn_params->ed->map->sectors,
			&btn_params->ed->linked_walls, &btn_params->ed->linked_walls_count);
	btn_params->ed->map_is_updated = e_false;
}

void	create_split_wall_button(t_editor *ed, int *y)
{
	SDL_Surface	*chars;
	t_i_coords	pos;
	t_button	btn;

	chars = write_text(ed->fonts->vcr20, "Split wall",
			(SDL_Colour){0x88, 0x88, 0xFF, 0});
	pos.x = PAN_PAD_L + 12;
	pos.y = *y;
	btn.rect = create_rect(pos.x - 12, pos.y - 12, chars->w + 24,
			chars->h + 24);
	fill_rect(ed->panel.surface, &btn.rect, WHITE, e_true);
	draw_on_screen(ed->panel.surface, chars, pos, e_false);
	SDL_FreeSurface(chars);
	btn.rect.pos.x += PANEL_X;
	btn.f = &split_wall;
	btn.params = create_btn_params(NULL, NULL, ed);
	add_button_to_list(&ed->panel.buttons, btn);
}

void	change_wall_in_window(t_params params)
{
	t_editor	*ed;

	ed = ((t_btn_params *)params)->ed;
	if (ed->selected.wall->type == e_wall)
		transform_wall_to_window(ed->selected.wall, ed->map->sectors->items[0]);
	else
		transform_window_to_wall(ed->selected.wall);
	ed->map_is_updated = e_false;
}

void	change_portal_to_door(t_params params)
{
	t_editor	*ed;

	ed = ((t_btn_params *)params)->ed;
	transform_portal_to_door(ed->selected.wall, ed->panel.walls.first->texture);
}

void	change_door_to_portal(t_params params)
{
	t_editor	*ed;

	ed = ((t_btn_params *)params)->ed;
	transform_door_to_portal(ed->selected.wall, ed->linked_walls);
}
