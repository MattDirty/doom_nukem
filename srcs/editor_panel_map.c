#include "editor.h"
#include "editor_draw.h"
#include "editor_panel.h"
#include "editor_panel_buttons.h"
#include "ui.h"

void		editor_draw_panel_map(t_editor *ed)
{
	int		y;

	write_panel_state(ed, "MAP");
	y = 60;
	ed->selected_sprite = &ed->map->daysky;
	draw_sprites_section(ed, &ed->panel.skies, "Skybox Day:", &y);
	y += 20;
	ed->selected_sprite = &ed->map->nightsky;
	draw_sprites_section(ed, &ed->panel.skies, "Skybox Night:", &y);
}