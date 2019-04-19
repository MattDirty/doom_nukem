/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pickables.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badhont <badhont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 04:22:46 by badhont           #+#    #+#             */
/*   Updated: 2019/04/18 10:32:48 by badhont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "pickables.h"
#include "doom.h"
#include "serialisation.h"
#include "e_bool.h"
#include "utils.h"
#include "sectors.h"

static  void    make_weapon_usable(t_weapons *node, Uint32 target)
{
    Uint32  i;

    i = 0;
    while (node && i < target)
    {
        node = node->next;
        i++;
    }
    node->item->usable = e_true;
}

t_pickables	*extract_pickable(
        t_pickables **pickables,
        t_pickable *pickable)
{
    t_pickables	*previous;
    t_pickables	*node;

    if (pickable == &(*pickables)->item)
    {
        previous = *pickables;
        *pickables = previous->next;
        previous->next = NULL;
        return (previous);
    }
    previous = NULL;
    node = *pickables;
    while (node)
    {
        if (&node->item == pickable)
        {
            previous->next = node->next;
            node->next = NULL;
            return (node);
        }
        previous = node;
        node = node->next;
    }
    return (NULL);
}

void	delete_pickable(t_pickables **pickables, t_pickable *to_delete)
{
    t_pickables *node;

    node = extract_pickable(pickables, to_delete);
    if (!node)
        return ;
    free(node->item.object);
    free(node);
}

void     do_stuff(t_player *player, t_pickables *pickables)
{
    if (pickables->item.type == et_gun)
        make_weapon_usable(player->weapons, 1);
    else if (pickables->item.type == et_shotgun)
        make_weapon_usable(player->weapons, 2);
    else if (pickables->item.type == et_vacuum)
        make_weapon_usable(player->weapons, 3);
    else
        error_doom("invalid pickable");
}

int         is_close_to(t_coords target, t_coords pos, double dist)
{
    if ((fabs(pos.x - target.x) < dist)
        && (fabs(pos.y - target.y) < dist))
        return (1);
    return (0);
}

void     pick_objects(t_player *player)
{
    t_pickables *pickables;
    t_coords    pick_pos;

    pickables = player->current_sector->pickables;
    pick_pos = (t_coords){
        pickables->item.object->x,
        pickables->item.object->y};
    while (pickables)
    {
        if (is_close_to(pick_pos, player->pos, 0.2))
        {
            do_stuff(player, pickables);
            delete_pickable(&player->current_sector->pickables, &pickables->item);
        }
        pickables = pickables->next;
    }
}

void    write_pickable_to_file(int fd, t_pickable pickable)
{
    write_object_to_file(fd, *pickable.object);
    if (write(fd, &pickable.type, sizeof(pickable.type)) <= 0)
        error_doom("Problem while type pickable from file");
    write_str_to_file(fd, pickable.sprite_to_pick[0]->userdata);
    write_str_to_file(fd, pickable.sprite_to_pick[1]->userdata);
    write_str_to_file(fd, pickable.sprite_to_pick[2]->userdata);
}

void    read_pickable_from_file(int fd, t_textures *textures, t_pickable *pickable)
{
    if (!(pickable->object = (t_object *)malloc(sizeof(t_object))))
        error_doom("Couldn't allocate object in pickable");
    read_object_from_file(fd, textures, pickable->object);
    if (read(fd, &pickable->type, sizeof(pickable->type)) <= 0)
        error_doom("Problem while reading pickable from file");
    find_texture_from_file(fd, textures, &pickable->sprite_to_pick[0]);
    find_texture_from_file(fd, textures, &pickable->sprite_to_pick[1]);
    find_texture_from_file(fd, textures, &pickable->sprite_to_pick[2]);
}

void    write_pickables_to_file(int fd, t_pickables *pickables)
{
    enum e_bool	next;

    next = pickables != NULL;
    if (write(fd, &next, sizeof(next)) <= 0)
        error_doom("mabite");
    if (!next)
        return;
    write_pickable_to_file(fd, pickables->item);
    write_pickables_to_file(fd, pickables->next);
}

void    read_pickables_from_file(
        int fd,
        t_textures *textures,
        t_pickables **pickables)
{
    enum e_bool	next;

    if (read(fd, &next, sizeof(next)) <= 0)
        error_doom("The shield has gone mad, Detroudbalus!");
    if (!next)
        return;
    if (!(*pickables = (t_pickables*)malloc(sizeof(t_pickables))))
        error_doom("Couldn't allocate pickables struct");
    (*pickables)->next = NULL;
    read_pickable_from_file(fd, textures, &(*pickables)->item);
    read_pickables_from_file(fd, textures, &(*pickables)->next);
}

void	add_pickable(t_pickables **pickables, t_pickables *pickable)
{
    t_pickables	*node;

    if (!*pickables)
    {
        *pickables = pickable;
        return;
    }
    node = *pickables;
    while (node->next)
        node = node->next;
    node->next = pickable;
}

int count_pickables(t_pickables *pickables)
{
    int i;

    i = 0;
    while (pickables)
    {
        pickables = pickables->next;
        i++;
    }
    return (i);
}

t_pickable      create_default_pickable(t_textures *textures)
{
    t_pickable  new_pickable;

    if (!(new_pickable.object = (t_object *)malloc(sizeof(t_object))))
        error_doom("Couldn't allocate object in pickable");
    *new_pickable.object = create_default_object(textures);
    new_pickable.type = et_gun;
    find_texture_by_name(textures, "textures/sprites/gun.bmp",
                         &new_pickable.sprite_to_pick[0]);
    find_texture_by_name(textures, "textures/sprites/shotgun.bmp",
                         &new_pickable.sprite_to_pick[1]);
    find_texture_by_name(textures, "textures/sprites/vacuum.bmp",
                         &new_pickable.sprite_to_pick[2]);
    return (new_pickable);
}

t_pickables    *add_new_pickable_to_sector_at_pos(t_sector *sector,
                                                    t_coords pos, t_textures *textures)
{
    t_pickables *new_pickables;

    if (count_pickables(sector->pickables) > 6)
        return (NULL);
    if (!(new_pickables = (t_pickables *)malloc(sizeof(t_pickables))))
        error_doom("couldn't allocate new pickable");
    new_pickables->next = NULL;
    new_pickables->item = create_default_pickable(textures);
    new_pickables->item.object->x = pos.x;
    new_pickables->item.object->y = pos.y;
    new_pickables->item.object->sprite = new_pickables->item.sprite_to_pick[0];
    add_pickable(&sector->pickables, new_pickables);
    return (new_pickables);
}

void	free_pickables(t_pickables *pickables)
{
    if (!pickables)
        return;
    free_pickables(pickables->next);
    free(pickables->item.object);
    free(pickables);
}
