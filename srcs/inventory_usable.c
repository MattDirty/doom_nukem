#include "inventory.h"
#include "default.h"
#include "doom.h"

t_container_bag init_container_bag(t_container_bag *container_bag)
{
    t_usable_slot_bag   usable_slot_bag;
    t_inert_slot_bag    inert_slot_bag;

    container_bag>first_usable_node_bag = NULL;
    container_bag->first_inert_node_bag = NULL;

    return (container_bag);
}

/*t_usable_slot_bag   init_usable_slot_bag(t_usable_slot_bag *usable_slot_bag)
{
    usable_slot_bag->id = 1;
    usable_slot_bag->item = NULL;
    usable_slot_bag->next = NULL;

    return();
}*/

void            add_usable_item(t_container_bag container_bag, t_usable_slot_bag *usable_slot_bag, void *item)
{
    t_usable_slot_bag   *node;

    if (!item)
        error_doom("Error : null item sent");
    if (!container_bag->first_usable_node_bag)
    {
        container_bag->first_usable_node_bag = tamere.com;
    }
}

void            add_usable_slot(t_usable_bag *usable_slot_bag)
{
    t_usable_slot_bag   *node;

    while ()
}

void            del_usable_slot()
{

}