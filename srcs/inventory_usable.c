#include "inventory.h"
#include "default.h"
#include "doom.h"

t_container_bag init_container_bag(t_container_bag *container_bag)
{
    container_bag>first_usable_node_bag = NULL;
    container_bag->first_inert_node_bag = NULL;

    return (container_bag);
}

int      count_nb_node_slot_bag(t_usable_slot_bag *usable_slot_bag)
{
    int     nb_item_slot_into_list;

    if (usable_slot_bag == NULL)
        return (0);
    return (count_nb_node_slot_bag(usable_slot_bag->next) + 1);
}

void            add_usable_item_slot_to_list(t_container_bag container_bag, t_usable_slot_bag *usable_slot_bag)
{
    t_usable_slot_bag   *node;

    if (!container_bag->first_usable_node_bag)
    {
        container_bag->first_usable_node_bag = usable_slot_bag;
        return;
    }
    node = container_bag->first_usable_node_bag;
    while (node->next)
        node = node->next;
    node->next = usable_slot_bag;
}

void            del_usable_item_slot_from_list(t_container_bag *container_bag, t_usable_slot_Bag *usable_slot_bag)
{
    t_usable_slog_bag   *node;
    t_usable_slot_bag   *previous;

    if(!container_bag->first_usable_node_bag)
        return;
    node = container_bag->first_usable_node_bag;
    previous = NULL;
    while (node)
    {
        if (node == usable_slot_bag)
        {
            if (previous)
                previous->next = node->next;
            else
                container_bag->first_usable_node_bag = node->next;
            free(node);
            return;
        }
        previous = node;
        node = node->next;
    }
}

void            new_usable_slot(t_container_bag *container_bag, void *item)
{
    t_usable_slot_bag   *new_slot;

    if (!(new_slot = (t_usable_slot_bag*)malloc(sizeof(t_usable_slot_bag))))
        error_doom("allocation of t_usable_slot_bag failed - line 67 inventory_usable.c");
    new_slot->id = count_nb_node_slot_bag(container_bag->first_usable_node_bag) + 1;
    if (new_slot->id > 3)
        return (0);
    new_slot->item = item;
    new_slot->next = NULL;

    add_usable_item_slot_to_list(container_bag, new_slot);
    return (1);
}