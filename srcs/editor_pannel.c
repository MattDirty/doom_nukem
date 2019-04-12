/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_pannel.c                                    :+:      :+:    :+:   */
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

void        click_on_pannel(t_editor *ed, t_buttons *buttons, int mouse_x, int mouse_y)
{
    int i;

    if (mouse_x < PANNEL_X)
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
    write_file("mabite.roflolilolmao", ed->textures, ed->map);
    draw_rect(ed->sdl.surface, rect, BLACK);
}

static void draw_save_button(SDL_Surface *target, t_buttons *buttons, int i)
{
    t_button    save_btn;
    SDL_Surface *save;
    t_coords    location;

    save_btn.rect = create_rect(PANNEL_X + 5, PANNEL_Y + 5, 40, 20);
    draw_rect(target, &save_btn.rect, RED);
    fill_rect(target, &save_btn.rect, PINK);
    save = write_text("fonts/sixty.ttf", 15, "SAVE", (SDL_Colour){255,0,0,255});
    location.x = save_btn.rect.pos.x + save_btn.rect.width / 2 - save->w / 2;
    location.y = save_btn.rect.pos.y + save_btn.rect.height / 2 - save->h / 2;
    draw_on_screen(target, save, location, t_false);
    save_btn.f = &save_editor;
    buttons->items[i] = save_btn;
    free(save);
}

void        draw_pannel(t_editor *ed)
{
    t_rect  pannel;

    pannel = create_rect(PANNEL_X, PANNEL_Y,
                         EDITOR_W - PANNEL_X - 1, EDITOR_H - 1);
    draw_rect(ed->sdl.surface, &pannel, WHITE);
    fill_rect(ed->sdl.surface, &pannel, DARK_BLUE);
    draw_save_button(ed->sdl.surface, &ed->buttons, 0);
}