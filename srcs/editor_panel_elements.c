#include "editor.h"
#include "ui.h"
#include "editor_panel_buttons.h"

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

void		editor_draw_panel_walls(t_editor *ed)
{
    int		y;

    write_panel_state(ed, "WALLS");
    y = 60;
    if (ed->selected.wall->type == e_portal)
        ed->selected_sprite = NULL;
    else
        ed->selected_sprite = &ed->selected.wall->texture;
    draw_sprites_section(ed, &ed->panel.walls, "Walls:", &y);
    draw_sprites_section(ed, &ed->panel.flats, " ", &y);
    y += 20;
    if (ed->selected.wall->wall_object)
        ed->selected_sprite = &ed->selected.wall->wall_object->texture;
    else if (ed->selected.wall->lever)
        ed->selected_sprite = &ed->selected.wall->lever->wall_object->texture;
    draw_sprites_section(ed, &ed->panel.wall_objects, "Wall objects:", &y);
}

void		editor_draw_panel_sprites(t_editor *ed)
{
    int		y;

    write_panel_state(ed, "SPRITES");
    y = 60;
    if (ed->selected.object)
        ed->selected_sprite = &ed->selected.object->sprite;
    else if (ed->selected.enemy)
        ed->selected_sprite = &ed->selected.enemy->front;
    draw_sprites_section(ed, &ed->panel.sprites, "Sprites:", &y);
}

void    create_light_btn(TTF_Font *font, SDL_Surface *target, Uint32 light_color, t_editor *ed)
{
    SDL_Surface *light;
    t_i_coords pos;
    t_button    light_btn;

    light = write_text(font, "Light", (SDL_Colour) {255, 255, 255, 255});
    pos.x = PANEL_PADDING_LEFT + 10;
    pos.y = PANEL_H - light->h - 50;
    light_btn.rect = create_rect(pos.x - 6, pos.y - 6, light->w + 10, light->h + 10);
    draw_rect(target, &light_btn.rect, WHITE);
    fill_rect(target, &light_btn.rect, WHITE, t_false);
    fill_rect(target, &light_btn.rect, light_color, t_true);
    draw_on_screen(target, light, pos, t_false);
    light_btn.f = &toggle_lighting;
    light_btn.params = create_btn_params(NULL, NULL, ed);
    add_button_to_list(&ed->panel.buttons, light_btn);
    SDL_FreeSurface(light);
}
void        editor_draw_panel_sector(t_editor *ed)
{
    int     y;

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
    create_light_btn(ed->fonts->vcr40, ed->panel.surface, ed->selected.sector->light, ed);
}