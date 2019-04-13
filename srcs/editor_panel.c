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

void        click_on_panel(t_editor *ed, t_buttons *buttons, int mouse_x, int mouse_y)
{
    int i;

    if (mouse_x < panel_X)
        return ;
    i = 0;
    while (i < buttons->count)
    {
        if (is_in_rect(&buttons->items[i].rect, mouse_x, mouse_y))
        {
            buttons->items[i].f(ed, &buttons->items[i].rect);
            return ;
        }
        i++;
    }

}

static void save_editor(t_editor *ed, t_rect *rect)
{
    write_file(ed->map_path, ed->textures, ed->map);
    draw_rect(ed->sdl.surface, rect, BLACK);
}

void draw_save_button(TTF_Font *font, SDL_Surface *target, t_buttons *buttons, int i)
{
    t_button    save_btn;
    SDL_Surface *save;
    t_coords    location;

    save_btn.rect = create_rect(panel_X + 5, panel_Y + 5, 40, 20);
    draw_rect(target, &save_btn.rect, RED);
    fill_rect(target, &save_btn.rect, PINK);
    save = write_text(font, "SAVE", (SDL_Colour){255,0,0,255});
    location.x = save_btn.rect.pos.x + save_btn.rect.width / 2 - save->w / 2;
    location.y = save_btn.rect.pos.y + save_btn.rect.height / 2 - save->h / 2;
    draw_on_screen(target, save, location, t_false);
    save_btn.f = &save_editor;
    buttons->items[i] = save_btn;
    free(save);
}

static void draw_texture_btn(SDL_Surface *target, SDL_Surface *texture, t_i_coords pos)
{
    t_button    text_btn;
    int         x;
    int         y;
    t_i_coords  text;
    Uint32      color;

    text_btn.rect = create_rect(pos.x, pos.y, 40, 40);
    draw_rect(target, &text_btn.rect, GREEN);
    y = text_btn.rect.pos.y + 1;
    text.y = 0;
    while (y < (text_btn.rect.pos.y + text_btn.rect.height))
    {
        x = text_btn.rect.pos.x + 1;
        text.x = 0;
        while (x < (text_btn.rect.pos.x + text_btn.rect.width - 1))
        {
            color = get_pixel(texture, text.x, text.y, t_true);
            put_pixel(target, x, y, color);
            x++;
            text.x += texture->w / 40;
        }
        y++;
        text.y += texture->h / 40;
    }
}

void        get_all_text(t_editor *ed)
{
    t_texture_node *n;
    t_texture_node *p;
    t_i_coords      pos;

    pos.x = panel_X + 5;
    pos.y = panel_Y + 35;
    n = ed->textures->first;
    while (n)
    {
        p = n;
        n = n->next;
        draw_texture_btn(ed->sdl.surface, p->texture, pos);
        if (pos.x >= EDITOR_W - 75)
        {
            pos.x = panel_X + 5;
            pos.y += 45;
        }
        else
            pos.x += 43;
    }
}

void        draw_panel(t_editor *ed)
{
    t_rect  panel;

    panel = create_rect(panel_X, panel_Y,
                         EDITOR_W - panel_X - 1, EDITOR_H - 1);
    draw_rect(ed->sdl.surface, &panel, WHITE);
    fill_rect(ed->sdl.surface, &panel, DARK_BLUE);
    draw_save_button(ed->fonts->sixty20, ed->sdl.surface, &ed->buttons, 0);
    get_all_text(ed);
}