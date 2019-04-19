#include "doom.h"
#include "editor_panel_buttons.h"

t_btn_params    *create_btn_params(
        SDL_Surface **selected, SDL_Surface *target, t_editor *ed)
{
    t_btn_params *params;

    if (!(params = (t_btn_params *)malloc(sizeof(t_btn_params))))
        error_doom("Couldn't malloc button params");
    params->selected = selected;
    params->target = target;
    params->ed = ed;
    return (params);
}

void    add_button_to_list(t_buttons **list, t_button button)
{
    t_buttons *new_n;
    t_buttons *n;

    if (!(new_n = (t_buttons *)malloc(sizeof(t_buttons))))
        error_doom("Couldn't malloc button");
    new_n->item = button;
    new_n->next = NULL;
    if (!*list)
    {
        *list = new_n;
        return ;
    }
    n = *list;
    while (n->next)
        n = n->next;
    n->next = new_n;
}

void    free_buttons_list(t_buttons *n)
{
    t_buttons   *next;

    while (n)
    {
        next = n->next;
        free(n->item.params);
        free(n);
        n = next;
    }
}