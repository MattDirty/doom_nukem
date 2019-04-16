#ifndef EDITOR_PANEL_BUTTONS_H
# define EDITOR_PANEL_BUTTONS_H

#include "editor.h"

typedef struct			s_button
{
    t_rect				rect;
    void				(*f)(t_editor *ed, t_rect *rect);
}						t_button;

typedef struct			s_buttons
{
    t_button			item;
    struct s_buttons    *next;
}						t_buttons;

#endif
