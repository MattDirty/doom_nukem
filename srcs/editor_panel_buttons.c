#include "doom.h"
#include "editor_panel_buttons.h"

void    add_button_to_list(t_buttons *list, t_button button)
{
    t_buttons *new_node;

    new_node = list;
    if (!new_node)
    {
        if (!(list = (t_buttons *)malloc(sizeof(t_buttons))))
            error_doom("Couldn't malloc button");
        new_node->next = NULL;
        new_node->item = button;
        return ;
    }
    while (new_node->next)
        new_node = new_node->next;
    if (!(new_node->next = (t_buttons *)malloc(sizeof(t_buttons))))
        error_doom("Couldn't malloc button");
    new_node = new_node->next;
    new_node->item = button;
    new_node->next = NULL;
}

void    free_buttons_list(t_buttons *node)
{
    t_buttons   *next;

    while (node)
    {
        next = node->next;
        free(node);
        node = next;
    }
}