#ifndef INVENTORY_H
# define INVENTORY_H

# include "SDL.h"
# include "config.h"

typedef struct      s_usable_slot_bag
{
    int                         id;
    void                        *item;
    struct s_usable_slot_bag    *next;
}                   t_usable_slot_bag;

typedef struct      s_inert_slot_bag
{
    int                         id;
    void                        *item;
    struct s_inert_slot_bag     *next;
}                   t_inert_slot_bag;

typedef struct      s_container_bag
{
    t_usable_slot_bag   *first_usable_node_bag;
    t_inert_slot_bag    *first_inert_node_bag;
}                   t_container_bag;

t_container_bag        init_container_bag(t_container_bag *container_bag);

int             count_nb_node_usable_slot_bag(t_usable_slot_bag *usable_slot_bag);
int             count_nb_node_inert_slot_bag(t_inert_slot_bag *inert_slot_bag);

void            add_usable_item_slot_to_list(t_container_bag *container_bag, t_usable_slot_bag *usable_slot_bag);
void            del_usable_item_slot_from_list(t_container_bag *container_bag, t_usable_slot_bag *usable_slot_bag);
int             new_usable_slot(t_container_bag *container_bag, void *item);

void            add_inert_item_slot_to_list(t_container_bag *container_bag, t_inert_slot_bag *inert_slot_bag);
void            del_inert_item_slot_from_list(t_container_bag *container_bag, t_inert_slot_bag *inert_slot_bag);
int             new_inert_slot(t_container_bag *container_bag, void *item);

#endif