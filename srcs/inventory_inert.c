#include "inventory.h"
#include "doom.h"

int      count_nb_node_inert_slot_bag(t_inert_slot_bag *inert_slot_bag)
{
    int     nb_item_slot_into_list;

    nb_item_slot_into_list = 0;
    if (inert_slot_bag == NULL)
        return (0);
    while (inert_slot_bag->next)
        nb_item_slot_into_list++;
    return (nb_item_slot_into_list);
}

void            add_inert_item_slot_to_list(t_container_bag *container_bag, t_inert_slot_bag *inert_slot_bag)
{
    t_inert_slot_bag   *node;

    if (!container_bag->first_inert_node_bag)
    {
        container_bag->first_inert_node_bag = inert_slot_bag;
        return;
    }
    node = container_bag->first_inert_node_bag;
    while (node->next)
        node = node->next;
    node->next = inert_slot_bag;
}

void            del_inert_item_slot_from_list(t_container_bag *container_bag, t_inert_slot_bag *inert_slot_bag)
{
    t_inert_slot_bag   *node;
    t_inert_slot_bag   *previous;

    if(!container_bag->first_inert_node_bag)
        return;
    node = container_bag->first_inert_node_bag;
    previous = NULL;
    while (node)
    {
        if (node == inert_slot_bag)
        {
            if (previous)
                previous->next = node->next;
            else
                container_bag->first_inert_node_bag = node->next;
            free(node);
            return;
        }
        previous = node;
        node = node->next;
    }
}

int             new_inert_slot(t_container_bag *container_bag, void *item)
{
    t_inert_slot_bag   *new_slot;

    if (!(new_slot = (t_inert_slot_bag*)malloc(sizeof(t_inert_slot_bag))))
        error_doom("allocation of t_inert_slot_bag failed - line 49 inventory_inert.c");
    new_slot->id = count_nb_node_inert_slot_bag(container_bag->first_inert_node_bag) + 1;
    if (new_slot->id > 3)
        return (0);
    new_slot->item = item;
    new_slot->next = NULL;

    add_inert_item_slot_to_list(container_bag, new_slot);
    return (1);
}

