#include "editor.h"
#include "editor_draw.h"
#include "editor_panel.h"
#include "editor_panel_buttons.h"
#include "ui.h"

void save_editor(t_editor *ed, t_rect *rect)
{
	write_file(ed->map_path, ed->textures, ed->map);
	draw_rect(ed->sdl.surface, rect, BLACK);
}

void draw_save_button(TTF_Font *font, SDL_Surface *target)
{
	SDL_Surface *save;
	t_i_coords  pos;
	t_rect      center;
	t_button    save_btn;

	save = write_text(font, "SAVE", (SDL_Colour){255,255,255,255});
	pos.x = PANEL_W - save->w - 100;
	pos.y = PANEL_H - save->h - 30;
	save_btn.rect = create_rect(
			pos.x - 12, pos.y - 12, save->w + 24, save->h + 8);
	center = create_rect(pos.x - 8, pos.y - 8, save->w + 16, save->h + 0);
	fill_rect(target, &save_btn.rect, SAVE_BORDER);
	fill_rect(target, &center, SAVE_CENTER);
	draw_on_screen(target, save, pos, t_false);
	SDL_FreeSurface(save);
}

void		editor_draw_panel_map(t_editor *ed)
{
	int		y;

	write_panel_state(ed, "MAP");
	y = 60;
	draw_save_button(ed->fonts->amazdoom40, ed->panel.surface);
	ed->selected_sprite_str = ed->map->daysky->userdata;
	draw_sprites_section(ed, &ed->panel.skies, "Skybox Day:", &y);
	y += 20;
	ed->selected_sprite_str = ed->map->nightsky->userdata;
	draw_sprites_section(ed, &ed->panel.skies, "Skybox Night:", &y);
}