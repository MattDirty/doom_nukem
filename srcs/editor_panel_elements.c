#include "editor.h"

void		editor_draw_panel_walls(t_editor *ed)
{
    int		y;

    write_panel_state(ed, "WALLS");
    y = 60;
    if (ed->selected.wall->type == e_portal)
        ed->selected_sprite_str = NULL;
    else
        ed->selected_sprite_str = ed->selected.wall->texture->userdata;
    draw_sprites_section(ed, &ed->panel.walls, "Walls:", &y);
    draw_sprites_section(ed, &ed->panel.flats, " ", &y);
    y += 20;
    if (ed->selected.wall->wall_object)
        ed->selected_sprite_str = ed->selected.wall->wall_object->texture->userdata;
    else if (ed->selected.wall->lever)
        ed->selected_sprite_str = ed->selected.wall->lever->wall_object->texture->userdata;
    draw_sprites_section(ed, &ed->panel.wall_objects, "Wall objects:", &y);
}

void		editor_draw_panel_sprites(t_editor *ed)
{
    int		y;

    write_panel_state(ed, "SPRITES");
    y = 60;
    if (ed->selected.object)
        ed->selected_sprite_str = ed->selected.object->sprite->userdata;
    else if (ed->selected.enemy)
        ed->selected_sprite_str = ed->selected.enemy->front->userdata;
    draw_sprites_section(ed, &ed->panel.sprites, "Sprites:", &y);
}

void        editor_draw_panel_sector(t_editor *ed)
{
    int     y;

    write_panel_state(ed, "SECTOR");
    y = 60;
    ed->selected_sprite_str = ed->selected.sector->floor->userdata;
    draw_sprites_section(ed, &ed->panel.walls, "Floor:", &y);
    draw_sprites_section(ed, &ed->panel.flats, " ", &y);
    y += 20;
    if (!(ed->selected.sector->open_sky))
        ed->selected_sprite_str = ed->selected.sector->ceil->userdata;
    else
        ed->selected_sprite_str = NULL;
    draw_sprites_section(ed, &ed->panel.walls, "Ceiling:", &y);
    draw_sprites_section(ed, &ed->panel.flats, " ", &y);
}