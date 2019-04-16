#include "editor.h"
#include "editor_panel_buttons.h"
#include "ui.h"
#include "walls.h"

t_sector    *find_wall_sector(t_sectors *sectors, t_wall *wall)
{
    int     i;
    int     j;

    i = 0;
    while (i < sectors->count)
    {
        j = 0;
        while (j < sectors->items[i].walls->count)
        {
            if (sectors->items[i].walls->items[j] == wall)
                return (&sectors->items[i]);
            j++;
        }
        i++;
    }
    return (NULL);
}

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

    chars = write_text(ed->fonts->vcr20, "Split wall", (SDL_Colour){255, 255, 255, 255});
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
    y += 40;
    create_split_wall_button(ed, &y);
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
    light_btn.rect.pos.x += PANEL_X;
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