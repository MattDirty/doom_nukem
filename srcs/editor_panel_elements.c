#include "editor.h"
#include "editor_panel_buttons.h"
#include "editor_mouse_clicks.h"
#include "ui.h"
#include "walls.h"
#include "editor_states.h"



void change_window_in_wall_button(t_editor *ed, int *y)
{
	SDL_Surface *chars;
	t_i_coords pos;
	t_button btn;
	chars = write_text(ed->fonts->vcr20, "Transform in wall",
					   (SDL_Colour){255, 0, 0, 0});
	pos.x = PAN_PAD_L + 12;
	pos.y = *y;
	btn.rect = create_rect(pos.x - 12, pos.y - 12, chars->w + 24,
						   chars->h + 24);
	fill_rect(ed->panel.surface, &btn.rect, WHITE, e_true);
	draw_on_screen(ed->panel.surface, chars, pos, e_false);
	SDL_FreeSurface(chars);
	btn.rect.pos.x += PANEL_X;
	btn.f = &change_wall_in_window;
	btn.params = create_btn_params(NULL, NULL, ed);
	add_button_to_list(&ed->panel.buttons, btn);
}

void change_wall_in_window_button(t_editor *ed, int *y)
{
	SDL_Surface *chars;
	t_i_coords pos;
	t_button btn;
	chars = write_text(ed->fonts->vcr20, "Transform in window",
					   (SDL_Colour){0, 0, 255, 0});
	pos.x = PAN_PAD_L + 12;
	pos.y = *y;
	btn.rect = create_rect(pos.x - 12, pos.y - 12, chars->w + 24,
						   chars->h + 24);
	fill_rect(ed->panel.surface, &btn.rect, WHITE, e_true);
	draw_on_screen(ed->panel.surface, chars, pos, e_false);
	SDL_FreeSurface(chars);
	btn.rect.pos.x += PANEL_X;
	btn.f = &change_wall_in_window;
	btn.params = create_btn_params(NULL, NULL, ed);
	add_button_to_list(&ed->panel.buttons, btn);
}

void create_new_sector_button(t_editor *ed, int *y)
{
	SDL_Surface *chars;
	t_i_coords pos;
	t_button btn;
	chars = write_text(ed->fonts->vcr20, "New Sector",
					   (SDL_Colour){0, 0, 0, 0});
	pos.x = PAN_PAD_L + 172;
	pos.y = *y;
	btn.rect = create_rect(pos.x - 12, pos.y - 12, chars->w + 24,
						   chars->h + 24);
	fill_rect(ed->panel.surface, &btn.rect, WHITE, e_true);
	draw_on_screen(ed->panel.surface, chars, pos, e_false);
	SDL_FreeSurface(chars);
	btn.rect.pos.x += PANEL_X;
	btn.f = &new_sector_state;
	btn.params = create_btn_params(NULL, NULL, ed);
	add_button_to_list(&ed->panel.buttons, btn);
}


void create_transform_portal_to_door_button(t_editor *ed, int *y)
{
	SDL_Surface *chars;
	t_i_coords pos;
	t_button btn;

	chars = write_text(ed->fonts->vcr20, "Transform in door",
					   (SDL_Colour){0, 0, 255, 0});
	pos.x = PAN_PAD_L + 12;
	pos.y = *y;
	btn.rect = create_rect(pos.x - 12, pos.y - 12, chars->w + 24,
						   chars->h + 24);
	fill_rect(ed->panel.surface, &btn.rect, WHITE, e_true);
	draw_on_screen(ed->panel.surface, chars, pos, e_false);
	SDL_FreeSurface(chars);
	btn.rect.pos.x += PANEL_X;
	btn.f = &change_portal_to_door;
	btn.params = create_btn_params(NULL, NULL, ed);
	add_button_to_list(&ed->panel.buttons, btn);
}

void create_transform_door_to_portal_button(t_editor *ed, int *y)
{
	SDL_Surface *chars;
	t_i_coords pos;
	t_button btn;

	chars = write_text(ed->fonts->vcr20, "Transform in portal",
					   (SDL_Colour){255, 0, 0, 0});
	pos.x = PAN_PAD_L + 12;
	pos.y = *y;
	btn.rect = create_rect(pos.x - 12, pos.y - 12, chars->w + 24,
						   chars->h + 24);
	fill_rect(ed->panel.surface, &btn.rect, WHITE, e_true);
	draw_on_screen(ed->panel.surface, chars, pos, e_false);
	SDL_FreeSurface(chars);
	btn.rect.pos.x += PANEL_X;
	btn.f = &change_door_to_portal;
	btn.params = create_btn_params(NULL, NULL, ed);
	add_button_to_list(&ed->panel.buttons, btn);
}

void highlight_selected_wall(t_editor *ed)
{
	t_segment s;

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

void create_add_door_lever_button(t_editor *ed, int *y)
{
	SDL_Surface *chars;
	t_i_coords pos;
	t_button btn;

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

void draw_panel_wall_buttons(t_editor *ed, t_wall *wall, int *y)
{
	t_sector *sector;

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
	} else
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

void write_panel_wall_state(t_editor *ed, t_wall *wall)
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

void editor_draw_panel_walls(t_editor *ed)
{
	int y;
	t_wall *wall;

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

void add_object_btn(t_editor *ed, TTF_Font *font, SDL_Surface *target, int *y)
{
	SDL_Surface *add_object;
	t_i_coords pos;
	t_button object_btn;

	add_object = write_text(font, "Add object", (SDL_Colour){255, 0, 0, 255});
	pos.x = PAN_PAD_L + 8;
	pos.y = *y - 35;
	object_btn.rect = create_rect(pos.x - 6, pos.y - 6, add_object->w + 10,
								  add_object->h + 10);
	draw_rect(target, &object_btn.rect, BLACK);
	fill_rect(target, &object_btn.rect, OBJECT_COLOR, e_true);
	draw_on_screen(target, add_object, pos, e_false);
	object_btn.rect.pos.x += PANEL_X;
	object_btn.f = &create_object_in_map_state;
	object_btn.params = create_btn_params(NULL, NULL, ed);
	add_button_to_list(&ed->panel.buttons, object_btn);
	SDL_FreeSurface(add_object);
}

void remove_selected_enemy(t_editor *ed)
{
	t_sector *sector;

	sector = find_enemy_sector(ed->map->sectors, ed->selected.enemy);
	delete_enemy(&sector->enemies, ed->selected.enemy);
	clear_selection(&ed->selected);
	ed->map_is_updated = e_false;
}

void remove_selected_pickable(t_editor *ed)
{
	t_sector *sector;

	sector = find_pickable_sector(ed->map->sectors, ed->selected.pickable);
	delete_pickable(&sector->pickables, ed->selected.pickable);
	clear_selection(&ed->selected);
	ed->map_is_updated = e_false;
}

void remove_selected_object(t_params params)
{
	t_object *object;
	t_sector *sector;
	t_editor *ed;

	ed = ((t_btn_params *)params)->ed;
	if (ed->selected.enemy && ed->selected.enemy->type)
	{
		remove_selected_enemy(ed);
		return;
	}
	if (ed->selected.pickable)
	{
		remove_selected_pickable(ed);
		return;
	}
	object = ed->selected.object;
	sector = find_object_sector(ed->map->sectors, object);
	remove_object(object, sector->objects);
	clear_selection(&ed->selected);
	ed->map_is_updated = e_false;
}

void remove_btn(t_editor *ed, TTF_Font *font, SDL_Surface *target, int *y)
{
	SDL_Surface *add_enemy;
	t_i_coords pos;
	t_button enemy_btn;

	add_enemy = write_text(font, "Remove", (SDL_Colour){255, 0, 0, 255});
	pos.x = PAN_PAD_L + 8;
	pos.y = *y - 35;
	enemy_btn.rect = create_rect(pos.x - 6, pos.y - 6, add_enemy->w + 10,
								 add_enemy->h + 10);
	draw_rect(target, &enemy_btn.rect, BLACK);
	fill_rect(target, &enemy_btn.rect, ENEMY_COLOR, e_true);
	draw_on_screen(target, add_enemy, pos, e_false);
	enemy_btn.rect.pos.x += PANEL_X;
	enemy_btn.f = &remove_selected_object;
	enemy_btn.params = create_btn_params(NULL, NULL, ed);
	add_button_to_list(&ed->panel.buttons, enemy_btn);
	SDL_FreeSurface(add_enemy);
}

void add_enemy_btn(t_editor *ed, TTF_Font *font, SDL_Surface *target, int *y)
{
	SDL_Surface *add_enemy;
	t_i_coords pos;
	t_button enemy_btn;

	add_enemy = write_text(font, "Add enemy ", (SDL_Colour){255, 0, 0, 255});
	pos.x = PAN_PAD_L + 8;
	pos.y = *y - 35;
	enemy_btn.rect = create_rect(pos.x - 6, pos.y - 6, add_enemy->w + 10,
								 add_enemy->h + 10);
	draw_rect(target, &enemy_btn.rect, BLACK);
	fill_rect(target, &enemy_btn.rect, ENEMY_COLOR, e_true);
	draw_on_screen(target, add_enemy, pos, e_false);
	enemy_btn.rect.pos.x += PANEL_X;
	enemy_btn.f = &create_enemy_in_map_state;
	enemy_btn.params = create_btn_params(NULL, NULL, ed);
	add_button_to_list(&ed->panel.buttons, enemy_btn);
	SDL_FreeSurface(add_enemy);
}

void add_weapon_btn(t_editor *ed, TTF_Font *font, SDL_Surface *target, int *y)
{
	SDL_Surface *add_weapon;
	t_i_coords pos;
	t_button weapon_btn;

	add_weapon = write_text(font, "Add weapon", (SDL_Colour){255, 0, 0, 255});
	pos.x = PAN_PAD_L + 8;
	pos.y = *y - 35;
	weapon_btn.rect = create_rect(pos.x - 6, pos.y - 6, add_weapon->w + 10,
								  add_weapon->h + 10);
	draw_rect(target, &weapon_btn.rect, BLACK);
	fill_rect(target, &weapon_btn.rect, PICKABLE_COLOR, e_true);
	draw_on_screen(target, add_weapon, pos, e_false);
	weapon_btn.rect.pos.x += PANEL_X;
	weapon_btn.f = &create_pickable_in_map_state;
	weapon_btn.params = create_btn_params(NULL, NULL, ed);
	add_button_to_list(&ed->panel.buttons, weapon_btn);
	SDL_FreeSurface(add_weapon);
}

void editor_draw_panel_map(t_editor *ed)
{
	int y;

	write_panel_state(ed, "MAP");
	y = 60;
	ed->selected_sprite = &ed->map->daysky;
	draw_sprites_section(ed, &ed->panel.skies, "Skybox Day:", &y);
	y += 20;
	ed->selected_sprite = &ed->map->nightsky;
	draw_sprites_section(ed, &ed->panel.skies, "Skybox Night:", &y);
	y += 100;
	add_enemy_btn(ed, ed->fonts->vcr40, ed->panel.surface, &y);
	y += 70;
	add_object_btn(ed, ed->fonts->vcr40, ed->panel.surface, &y);
	y += 70;
	add_weapon_btn(ed, ed->fonts->vcr40, ed->panel.surface, &y);
}

void change_enemy_hp(t_params params)
{
	t_enemy *enemy;

	enemy = ((t_btn_params *)params)->ed->selected.enemy;
	enemy->life_remaining += ((t_btn_params *)params)->ed->multi_purpose_int;
	if (enemy->life_remaining < 5)
		enemy->life_remaining = 5;
	else
		((t_btn_params *)params)->ed->map_is_updated = e_false;
}

void change_object_width(t_params params)
{
	double *target;
	t_editor *ed;

	ed = ((t_btn_params *)params)->ed;
	if (ed->selected.enemy)
		target = &ed->selected.enemy->object->horizontal_size;
	else
		target = &ed->selected.object->horizontal_size;
	*target += (ed->multi_purpose_int / 100.0);
	if (*target < 0.05)
		*target = 0.05;
	else if (*target > 1)
		*target = 1;
	else
		ed->map_is_updated = e_false;
}

void change_object_z(t_params params)
{
	double *target;
	t_editor *ed;

	ed = ((t_btn_params *)params)->ed;
	if (ed->selected.enemy)
		target = &ed->selected.enemy->object->z;
	else
		target = &ed->selected.object->z;
	*target += (ed->multi_purpose_int / 100.0);
	if (*target < 0)
		*target = 0;
	else if (*target > 0.95)
		*target = 0.95;
	else
		ed->map_is_updated = e_false;
}

void change_object_height(t_params params)
{
	double *target;
	t_editor *ed;

	ed = ((t_btn_params *)params)->ed;
	if (ed->selected.enemy)
		target = &ed->selected.enemy->object->vertical_size;
	else
		target = &ed->selected.object->horizontal_size;
	*target += (ed->multi_purpose_int / 100.0);
	if (*target < 0.05)
		*target = 0.05;
	else if (*target > 1)
		*target = 1;
	else
		ed->map_is_updated = e_false;
}

void hp_btn(t_editor *ed, TTF_Font *font, SDL_Surface *target, int *y)
{
	SDL_Surface *chars;
	t_i_coords pos;
	t_button btn;
	char *str;

	str = ft_strjoinfree("HP : ",
						 ft_itoa(ed->selected.enemy->life_remaining), 2);
	chars = write_text(font, str, (SDL_Colour){255, 255, 255, 255});
	free(str);
	pos.x = PAN_PAD_L + 8;
	pos.y = *y - 35;
	btn.rect = create_rect(pos.x - 6, pos.y - 6, chars->w + 10, chars->h);
	draw_rect(target, &btn.rect, BLACK);
	fill_rect(target, &btn.rect, RED, e_true);
	draw_on_screen(target, chars, pos, e_false);
	btn.rect.pos.x += PANEL_X;
	btn.f = &change_enemy_hp;
	btn.params = create_btn_params(NULL, NULL, ed);
	add_button_to_list(&ed->panel.buttons, btn);
	SDL_FreeSurface(chars);
}

void width_btn(t_editor *ed, TTF_Font *font, SDL_Surface *target, int *y)
{
	SDL_Surface *chars;
	t_i_coords pos;
	t_button btn;
	char *str;

	if (ed->selected.enemy)
		str = ft_strjoinfree("Width : ",
							 ft_itoa(round(
									 ed->selected.enemy->object->horizontal_size *
									 100)),
							 2);
	else
		str = ft_strjoinfree("Width : ",
							 ft_itoa(round(
									 ed->selected.object->horizontal_size *
									 100)), 2);
	chars = write_text(font, str, (SDL_Colour){255, 255, 255, 255});
	free(str);
	pos.x = PAN_PAD_L + 8;
	pos.y = *y - 35;
	btn.rect = create_rect(pos.x - 6, pos.y - 6, chars->w + 12, chars->h + 12);
	draw_rect(target, &btn.rect, BLACK);
	fill_rect(target, &btn.rect, 0xFF00AA00, e_true);
	draw_on_screen(target, chars, pos, e_false);
	btn.rect.pos.x += PANEL_X;
	btn.f = &change_object_width;
	btn.params = create_btn_params(NULL, NULL, ed);
	add_button_to_list(&ed->panel.buttons, btn);
	SDL_FreeSurface(chars);
}

void height_btn(t_editor *ed, TTF_Font *font, SDL_Surface *target, int *y)
{
	SDL_Surface *chars;
	t_i_coords pos;
	t_button btn;
	char *str;

	if (ed->selected.enemy)
		str = ft_strjoinfree("Height : ",
							 ft_itoa(round(
									 ed->selected.enemy->object->vertical_size *
									 100)),
							 2);
	else
		str = ft_strjoinfree("Height : ",
							 ft_itoa(round(
									 ed->selected.object->vertical_size * 100)),
							 2);
	chars = write_text(font, str, (SDL_Colour){255, 255, 255, 255});
	free(str);
	pos.x = PAN_PAD_L + 8;
	pos.y = *y - 35;
	btn.rect = create_rect(pos.x - 6, pos.y - 6, chars->w + 12, chars->h + 12);
	draw_rect(target, &btn.rect, BLACK);
	fill_rect(target, &btn.rect, 0xFF00AA00, e_true);
	draw_on_screen(target, chars, pos, e_false);
	btn.rect.pos.x += PANEL_X;
	btn.f = &change_object_height;
	btn.params = create_btn_params(NULL, NULL, ed);
	add_button_to_list(&ed->panel.buttons, btn);
	SDL_FreeSurface(chars);
}

void z_btn(t_editor *ed, TTF_Font *font, SDL_Surface *target, int *y)
{
	SDL_Surface *chars;
	t_i_coords pos;
	t_button btn;
	char *str;

	if (ed->selected.enemy)
		str = ft_strjoinfree("Z axis : ",
							 ft_itoa(round(
									 ed->selected.enemy->object->z * 100)),
							 2);
	else
		str = ft_strjoinfree("Z axis : ",
							 ft_itoa(round(ed->selected.object->z * 100)), 2);
	chars = write_text(font, str, (SDL_Colour){255, 255, 255, 255});
	free(str);
	pos.x = PAN_PAD_L + 8;
	pos.y = *y - 35;
	btn.rect = create_rect(pos.x - 6, pos.y - 6, chars->w + 12, chars->h + 12);
	draw_rect(target, &btn.rect, BLACK);
	fill_rect(target, &btn.rect, 0xFF00AA00, e_true);
	draw_on_screen(target, chars, pos, e_false);
	btn.rect.pos.x += PANEL_X;
	btn.f = &change_object_z;
	btn.params = create_btn_params(NULL, NULL, ed);
	add_button_to_list(&ed->panel.buttons, btn);
	SDL_FreeSurface(chars);
}

void editor_draw_panel_enemy(t_editor *ed)
{
	int y;

	write_panel_state(ed, "Baddy");
	y = 120;
	if (ed->selected.enemy->type != et_boss)
		remove_btn(ed, ed->fonts->vcr20, ed->panel.surface, &y);
	y += 70;
	hp_btn(ed, ed->fonts->amazdoom40, ed->panel.surface, &y);
	y += 70;
	width_btn(ed, ed->fonts->vcr20, ed->panel.surface, &y);
	y += 50;
	height_btn(ed, ed->fonts->vcr20, ed->panel.surface, &y);
	y += 50;
	z_btn(ed, ed->fonts->vcr20, ed->panel.surface, &y);
}

void editor_draw_panel_pickable(t_editor *ed)
{
	int y;

	write_panel_state(ed, "Weapon");
	y = 120;
	remove_btn(ed, ed->fonts->vcr20, ed->panel.surface, &y);
	ed->selected_sprite = &ed->selected.pickable->object->sprite;
	draw_sprites_section(ed, &ed->panel.pickables, " ", &y);
}


void editor_draw_panel_object(t_editor *ed)
{
	int y;

	write_panel_state(ed, "Flower");
	y = 120;
	remove_btn(ed, ed->fonts->vcr20, ed->panel.surface, &y);
	y += 50;
	width_btn(ed, ed->fonts->vcr20, ed->panel.surface, &y);
	y += 50;
	height_btn(ed, ed->fonts->vcr20, ed->panel.surface, &y);
	y += 50;
	z_btn(ed, ed->fonts->vcr20, ed->panel.surface, &y);
}

void create_light_btn(TTF_Font *font, SDL_Surface *target, Uint32 light_color,
					  t_editor *ed)
{
	SDL_Surface *light;
	t_i_coords pos;
	t_button light_btn;

	if (!ed->selected.sector->light)
		light = write_text(font, "Lights off", (SDL_Colour){0, 0, 0, 255});
	else
		light = write_text(font, "Lights on ",
						   (SDL_Colour){255, 255, 255, 255});
	pos.x = PAN_PAD_L + 10;
	pos.y = PANEL_H - light->h - 50;
	light_btn.rect = create_rect(pos.x - 6, pos.y - 6, light->w + 10,
								 light->h + 10);
	draw_rect(target, &light_btn.rect, YELLOW);
	fill_rect(target, &light_btn.rect, WHITE, e_false);
	fill_rect(target, &light_btn.rect, light_color, e_true);
	draw_on_screen(target, light, pos, e_false);
	light_btn.rect.pos.x += PANEL_X;
	light_btn.f = &toggle_lighting;
	light_btn.params = create_btn_params(NULL, NULL, ed);
	add_button_to_list(&ed->panel.buttons, light_btn);
	SDL_FreeSurface(light);
}

void create_sky_toggle_btn(TTF_Font *font,
						   SDL_Surface *target,
						   t_editor *ed,
						   int *y)
{
	SDL_Surface *toggle;
	t_i_coords pos;
	t_button sky_btn;
	Uint32 sky_color;
	Uint32 outer_color;

	toggle = write_text(font, "Ceiling ", (SDL_Colour){0, 0, 0, 255});
	sky_color = SKY_OFF;
	outer_color = BLACK;
	if (ed->selected.sector->open_sky)
	{
		toggle = write_text(font, "Open sky", (SDL_Colour){0, 0, 0, 255});
		sky_color = SKY_ON;
		outer_color = RED;
	}
	pos.x = PAN_PAD_L + 205;
	pos.y = *y - 35;
	sky_btn.rect = create_rect(pos.x - 6, pos.y - 6, toggle->w + 10,
							   toggle->h + 10);
	draw_rect(target, &sky_btn.rect, outer_color);
	fill_rect(target, &sky_btn.rect, sky_color, e_true);
	draw_on_screen(target, toggle, pos, e_false);
	sky_btn.rect.pos.x += PANEL_X;
	sky_btn.f = &toggle_skybox;
	sky_btn.params = create_btn_params(NULL, NULL, ed);
	add_button_to_list(&ed->panel.buttons, sky_btn);
	SDL_FreeSurface(toggle);
}

void editor_draw_panel_sector(t_editor *ed)
{
	int y;

	write_panel_state(ed, "SECTOR");
	y = 60;
	ed->selected_sprite = &ed->selected.sector->floor;
	draw_sprites_section(ed, &ed->panel.walls, "Floor:", &y);
	draw_sprites_section(ed, &ed->panel.flats, " ", &y);
	y += 20;
	if (!(ed->selected.sector->open_sky))
		ed->selected_sprite = &ed->selected.sector->ceil;
	else
		ed->selected_sprite = NULL;
	draw_sprites_section(ed, &ed->panel.walls, "Ceiling:", &y);
	draw_sprites_section(ed, &ed->panel.flats, " ", &y);
	create_light_btn(ed->fonts->vcr40, ed->panel.surface,
					 ed->selected.sector->light, ed);
	create_sky_toggle_btn(ed->fonts->vcr20, ed->panel.surface, ed, &y);
}


void toggle_skybox(t_params params)
{
	t_btn_params *ptr;

	ptr = (t_btn_params *)params;
	if (!ptr->ed->selected.sector->open_sky)
		ptr->ed->selected.sector->open_sky = e_true;
	else
	{
		ptr->ed->selected.sector->open_sky = e_false;
		ptr->ed->selected.sector->ceil = ptr->ed->selected.sector->floor;
	}
	ptr->ed->map_is_updated = e_false;
}

void toggle_lighting(t_params params)
{
	t_btn_params *ptr;

	ptr = (t_btn_params *)params;
	if (!ptr->ed->selected.sector->light)
		ptr->ed->selected.sector->light = 0xDD000000;
	else
		ptr->ed->selected.sector->light = 0;
	ptr->ed->map_is_updated = e_false;
}

void create_save_button(TTF_Font *font,
						SDL_Surface *target, t_panel *panel, t_editor *ed)
{
	SDL_Surface *save;
	t_i_coords pos;
	t_rect center;
	t_button save_btn;

	save = write_text(font, "SAVE", (SDL_Colour){255, 255, 255, 255});
	pos.x = PANEL_W - save->w - 100;
	pos.y = PANEL_H - save->h - 30;
	save_btn.rect = create_rect(
			pos.x - 12, pos.y - 12, save->w + 24, save->h + 8);
	center = create_rect(pos.x - 8, pos.y - 8, save->w + 16, save->h + 0);
	fill_rect(target, &save_btn.rect, SAVE_BORDER, e_false);
	fill_rect(target, &center, SAVE_CENTER, e_false);
	draw_on_screen(target, save, pos, e_false);
	save_btn.rect.pos.x += PANEL_X;
	save_btn.f = &save_editor;
	save_btn.params = create_btn_params(NULL, NULL, ed);
	add_button_to_list(&panel->buttons, save_btn);
	SDL_FreeSurface(save);
}