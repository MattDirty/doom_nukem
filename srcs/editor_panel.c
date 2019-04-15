/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_panel.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfatton <lfatton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 02:45:22 by lfatton           #+#    #+#             */
/*   Updated: 2019/04/12 02:45:24 by lfatton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"
#include "editor_draw.h"
#include "ui.h"
#include "textures.h"

static void save_editor(t_editor *ed, t_button *btn)
{
    write_file(ed->map_path, ed->textures, ed->map);
    btn->outside_color = BLACK;
}

void draw_save_button(TTF_Font *font, SDL_Surface *target, t_buttons *buttons, int i)
{
    t_button    save_btn;
    SDL_Surface *save;
    t_i_coords  pos;

    save_btn.rect = create_rect(PANEL_X + 5, PANEL_Y + 5, 40, 20);
    draw_rect(target, &save_btn.rect, buttons->items[i].outside_color);
    fill_rect(target, &save_btn.rect, PINK);
    save = write_text(font, "SAVE", (SDL_Colour){0,0,0,255});
    pos.x = save_btn.rect.pos.x + save_btn.rect.width / 2 - save->w / 2;
    pos.y = save_btn.rect.pos.y + save_btn.rect.height / 2 - save->h / 2;
    draw_on_screen(target, save, pos, t_false);
    save_btn.f = &save_editor;
    buttons->items[i] = save_btn;
    SDL_FreeSurface(save);
}

void draw_texture(t_editor *ed, SDL_Surface *texture, int i)
{
    t_button    text_btn;
    t_i_coords  text;
    t_i_coords  pos;
    Uint32      color_text;

    text_btn.rect = create_rect(ed->text_pos.x, ed->text_pos.y, 40, 40);
    draw_rect(ed->sdl.surface, &text_btn.rect, ed->buttons.items[i].outside_color);
    pos.y = text_btn.rect.pos.y + 1;
    text.y = 0;
    while (pos.y < (text_btn.rect.pos.y + text_btn.rect.height))
    {
        pos.x = text_btn.rect.pos.x + 1;
        text.x = 0;
        while (pos.x < (text_btn.rect.pos.x + text_btn.rect.width - 1))
        {
            color_text = get_pixel(texture, text.x, text.y, t_true);
            put_pixel(ed->sdl.surface, pos.x, pos.y, color_text);
            pos.x++;
            text.x += texture->w / 40;
        }
        pos.y++;
        text.y += texture->h / 40;
    }
    ed->buttons.items[i] = text_btn;
    if (ed->index < 7)
        ed->index++;
    else
        ed->index = 0;
}

void        draw_all_text(t_editor *ed)
{
    t_texture_node *n;
    t_texture_node *p;
    int             i;

    ed->text_pos.x = PANEL_X + 5;
    n = ed->textures->first;
    ed->index = 0;
    while (n)
    {
        i = 1;
        p = n;
        if (ft_strstr(p->texture->userdata, "skybox"))
            add_texture(ed->sky_text, p);
        else if (ft_strstr(n->texture->userdata, "walls") || ft_strstr(n->texture->userdata, "flats"))
            add_texture(ed->wall_text, p);
        else if (ft_strstr(n->texture->userdata, "sprites") || ft_strstr(n->texture->userdata, "flag"))
            add_texture(ed->sprite_text, p);
        n = n->next;
    }
}

void        write_textures_categories(SDL_Surface *target, TTF_Font *font)
{
    SDL_Surface *category;
    t_i_coords  pos;

    pos.x = PANEL_X + 5;
    pos.y = PANEL_Y + 35;

    category = write_text(font, "SKY", (SDL_Colour){0,0,0,255});
    draw_on_screen(target, category, pos, t_false);
    pos.y += 70;
    category = write_text(font, "FLATS", (SDL_Colour){0,0,0,255});
    draw_on_screen(target, category, pos, t_false);
    pos.y += 70;
    category = write_text(font, "SPRITES", (SDL_Colour){0,0,0,255});
    draw_on_screen(target, category, pos, t_false);
    pos.y += 70;
    free(category);
}

void        draw_panel(t_editor *ed)
{
    t_rect  panel;

    panel = create_rect(PANEL_X, PANEL_Y,
                         EDITOR_W - PANEL_X - 1, EDITOR_H - 1);
    draw_rect(ed->sdl.surface, &panel, WHITE);
    fill_rect(ed->sdl.surface, &panel, DARK_BLUE);
    draw_save_button(ed->fonts->sixty20, ed->sdl.surface, &ed->buttons, 0);
    write_textures_categories(ed->sdl.surface, ed->fonts->sixty20);
    draw_all_text(ed);
}
