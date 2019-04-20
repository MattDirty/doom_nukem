/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_panel_wall.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfatton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/20 07:59:18 by lfatton           #+#    #+#             */
/*   Updated: 2019/04/20 07:59:21 by lfatton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"
#include "editor_panel_buttons.h"
#include "editor_mouse_clicks.h"
#include "ui.h"
#include "walls.h"
#include "editor_states.h"

void	create_add_door_lever_button(t_editor *ed, int *y)
{
	SDL_Surface	*chars;
	t_i_coords	pos;
	t_button	btn;

	chars = write_text(ed->fonts->vcr20, "Add lever",
			(SDL_Colour){255, 0, 0, 0});
	pos.x = PAN_PAD_L + 12;
	pos.y = *y;
	btn.rect = create_rect(pos.x - 12, pos.y - 12, chars->w + 24,
			chars->h + 24);
	if (ed->state != e_add_lever)
		fill_rect(ed->panel.surface, &btn.rect, WHITE, e_true);
	else
		fill_rect(ed->panel.surface, &btn.rect, 0xFFFFFF00, e_true);
	draw_on_screen(ed->panel.surface, chars, pos, e_false);
	SDL_FreeSurface(chars);
	btn.rect.pos.x += PANEL_X;
	btn.f = &add_lever_state;
	btn.params = create_btn_params(NULL, NULL, ed);
	add_button_to_list(&ed->panel.buttons, btn);
}

void	highlight_selected_wall(t_editor *ed)
{
	t_segment	s;

	s = ed->selected.wall->segment;
	s.x1 = ed->map_offset.x + s.x1 * ed->zoom;
	s.y1 = ed->map_offset.y - s.y1 * ed->zoom;
	s.x2 = ed->map_offset.x + s.x2 * ed->zoom;
	s.y2 = ed->map_offset.y - s.y2 * ed->zoom;
	if (ed->selected.wall->type == e_wall)
		draw_segment(ed->sdl.surface, s, YELLOW);
	else
		draw_segment(ed->sdl.surface, s, GREEN);
}

void	draw_panel_wall_buttons(t_editor *ed, t_wall *wall, int *y)
{
	t_sector	*sector;

	sector = find_wall_sector(ed->map->sectors, wall);
	if (wall->type == e_wall
		|| (wall->type == e_transparent_wall && wall->to_infinity))
	{
		if (get_segment_length(&wall->segment) >= 1
			&& sector->walls->count < 15)
			create_split_wall_button(ed, y);
		create_new_sector_button(ed, y);
		*y += 50;
		if (wall->type == e_wall)
			change_wall_in_window_button(ed, y);
		else
			change_window_in_wall_button(ed, y);
	}
	else
	{
		*y += 30;
		if (wall->type == e_portal)
			create_transform_portal_to_door_button(ed, y);
		else
		{
			create_transform_door_to_portal_button(ed, y);
			*y += 50;
			create_add_door_lever_button(ed, y);
		}
	}
}

void	write_panel_wall_state(t_editor *ed, t_wall *wall)
{
	if (wall->type == e_wall)
		write_panel_state(ed, "Wall");
	else if (wall->type == e_transparent_wall && wall->to_infinity)
		write_panel_state(ed, "Window");
	else if (wall->type == e_transparent_wall && !wall->to_infinity)
		write_panel_state(ed, "Door");
	else
		write_panel_state(ed, "Portal");
}

void	editor_draw_panel_walls(t_editor *ed)
{
	int		y;
	t_wall	*wall;

	wall = ed->selected.wall;
	write_panel_wall_state(ed, wall);
	y = 60;
	if (wall->type == e_portal)
		ed->selected_sprite = NULL;
	else
	{
		ed->selected_sprite = &wall->texture;
		draw_sprites_section(ed, &ed->panel.walls, "Walls:", &y);
		draw_sprites_section(ed, &ed->panel.flats, " ", &y);
		y += 20;
		if (wall->wall_object)
			ed->selected_sprite = &wall->wall_object->texture;
		else if (wall->lever)
			ed->selected_sprite = &wall->lever->wall_object->texture;
		draw_sprites_section(ed, &ed->panel.wall_objects, "Wall objects:", &y);
		y += 40;
	}
	draw_panel_wall_buttons(ed, wall, &y);
	highlight_selected_wall(ed);
}
