#include "editor.h"
#include "editor_panel_buttons.h"
#include "ui.h"
#include "walls.h"

void        split_wall(t_params params)
{
    t_btn_params    *btn_params;
    t_wall          *wall;
    t_sector        *sector;
    t_wall          *new_wall;

    btn_params = (t_btn_params *)params;
    wall = btn_params->ed->selected.wall;
    sector = find_wall_sector(btn_params->ed->map->sectors, wall);
    new_wall = create_wall_copy(wall);
    new_wall->segment.x1 += (new_wall->segment.x2 - new_wall->segment.x1) / 2;
    new_wall->segment.y1 += (new_wall->segment.y2 - new_wall->segment.y1) / 2;
    wall->segment.x2 = new_wall->segment.x1;
    wall->segment.y2 = new_wall->segment.y1;
	add_wall_to_sector(sector, new_wall);
    btn_params->ed->map_is_updated = t_false;
}

void        create_split_wall_button(t_editor *ed, int *y)
{
    SDL_Surface *chars;
    t_i_coords  pos;
    t_button    btn;

    chars = write_text(ed->fonts->vcr20, "Split wall",
            (SDL_Colour){255, 255, 255, 255});
    pos.x = PANEL_PADDING_LEFT + 12;
    pos.y = *y;
    btn.rect = create_rect(pos.x - 12, pos.y - 12, chars->w + 24, chars->h + 24);
    fill_rect(ed->panel.surface, &btn.rect, 0, t_true);
    draw_on_screen(ed->panel.surface, chars, pos, t_false);
    SDL_FreeSurface(chars);
    btn.rect.pos.x += PANEL_X;
    btn.f = &split_wall;
    btn.params = create_btn_params(NULL, NULL, ed);
    add_button_to_list(&ed->panel.buttons, btn);
}

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
    int		    y;
    t_wall      *wall;
    t_sector    *sector;

    wall = ed->selected.wall;
    write_panel_state(ed, "WALL");
    y = 60;
    if (wall->type == e_portal)
        ed->selected_sprite = NULL;
    else
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
    sector = find_wall_sector(ed->map->sectors, wall);
    if (wall->type == e_wall && get_segment_length(&wall->segment) >= 1
    && sector->walls->count < 15)
        create_split_wall_button(ed, &y);
}

void		editor_draw_panel_sprites(t_editor *ed)
{
    int		y;

    write_panel_state(ed, "SPRITE");
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

    if (!ed->selected.sector->light)
        light = write_text(font, "Lights off", (SDL_Colour) {0, 0, 0, 255});
    else
        light = write_text(font, "Lights on ", (SDL_Colour) {255, 255, 255, 255});
    pos.x = PANEL_PADDING_LEFT + 10;
    pos.y = PANEL_H - light->h - 50;
    light_btn.rect = create_rect(pos.x - 6, pos.y - 6, light->w + 10, light->h + 10);
    draw_rect(target, &light_btn.rect, YELLOW);
    fill_rect(target, &light_btn.rect, WHITE, t_false);
    fill_rect(target, &light_btn.rect, light_color, t_true);
    draw_on_screen(target, light, pos, t_false);
    light_btn.rect.pos.x += PANEL_X;
    light_btn.f = &toggle_lighting;
    light_btn.params = create_btn_params(NULL, NULL, ed);
    add_button_to_list(&ed->panel.buttons, light_btn);
    SDL_FreeSurface(light);
}

void    create_sky_toggle_btn(TTF_Font *font, SDL_Surface *target, t_editor *ed, int *y)
{
    SDL_Surface *toggle;
    t_i_coords  pos;
    t_button    sky_btn;
    Uint32      sky_color;
    Uint32      outer_color;

    toggle = write_text(font, "Ceiling ", (SDL_Colour) {0, 0, 0, 255});
    sky_color = SKY_OFF;
    outer_color = BLACK;
    if (ed->selected.sector->open_sky)
    {
        toggle = write_text(font, "Open sky", (SDL_Colour) {0, 0, 0, 255});
        sky_color = SKY_ON;
        outer_color = RED;
    }
    pos.x = PANEL_PADDING_LEFT + 205;
    pos.y = *y - 35;
    sky_btn.rect = create_rect(pos.x - 6, pos.y - 6, toggle->w + 10, toggle->h + 10);
    draw_rect(target, &sky_btn.rect, outer_color);
    fill_rect(target, &sky_btn.rect, sky_color, t_true);
    draw_on_screen(target, toggle, pos, t_false);
    sky_btn.rect.pos.x += PANEL_X;
    sky_btn.f = &toggle_skybox;
    sky_btn.params = create_btn_params(NULL, NULL, ed);
    add_button_to_list(&ed->panel.buttons, sky_btn);
    SDL_FreeSurface(toggle);
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
    create_sky_toggle_btn(ed->fonts->vcr20, ed->panel.surface, ed, &y);
}