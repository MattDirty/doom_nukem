#include "editor.h"
#include "editor_draw.h"
#include "editor_panel.h"
#include "editor_panel_buttons.h"
#include "ui.h"

void save_editor(t_params params)
{
    t_btn_params *ptr;

    ptr = (t_btn_params *)params;
	write_file(ptr->ed->map_path, ptr->ed->textures, ptr->ed->map);
}

void create_save_button(TTF_Font *font,
        SDL_Surface *target, t_panel *panel, t_editor *ed)
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
	save_btn.rect.pos.x += PANEL_X;
    save_btn.f = &save_editor;
    save_btn.params = create_btn_params(NULL, NULL, ed);
    add_button_to_list(&panel->buttons, save_btn);
	SDL_FreeSurface(save);
}

void		editor_draw_panel_map(t_editor *ed)
{
	int		y;

	write_panel_state(ed, "MAP");
	y = 60;
	create_save_button(ed->fonts->amazdoom40, ed->panel.surface, &ed->panel, ed);
	ed->selected_sprite = &ed->map->daysky;
	draw_sprites_section(ed, &ed->panel.skies, "Skybox Day:", &y);
	y += 20;
	ed->selected_sprite = &ed->map->nightsky;
	draw_sprites_section(ed, &ed->panel.skies, "Skybox Night:", &y);
}