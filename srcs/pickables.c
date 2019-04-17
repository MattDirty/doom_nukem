/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pickables.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badhont <badhont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 04:22:46 by badhont           #+#    #+#             */
/*   Updated: 2019/04/17 07:45:58 by badhont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "pickables.h"
#include "doom.h"
#include "serialisation.h"
#include "e_bool.h"
#include "sectors.h"



/*enum e_bool pickable_death(double ms_since_update, t_params params)
{
    t_pickable *pickable;
    int     step;

    pickable = (t_pickable *)params;
    pickable->time_in_death += ms_since_update;

    step = (int)(pickable->time_in_death) / (int)(pickable->death_duration / 16);
    if (step >= 16)
        step = 15;
    pickable->object->sprite = pickable->explosion[step];
	if (pickable->time_in_death >= pickable->death_duration)
	{
		pickable->to_destroy = t_true;
		return (t_false);
	}
	return (t_true);
}*/

/*void    damage_pickable(t_timer_handler *timer_handler, t_pickable *pickable, Uint32 damage)
{
    pickable->life_remaining -= damage;
    if (pickable->life_remaining <= 0 && (int)pickable->time_in_death <= 0)
    {
        pickable->death_duration = 1700;
    	pickable->time_in_death = 1;
        add_event(
                timer_handler,
                1,
                &pickable_death,
                pickable
        );
    }
}*/

static void     do_stuff(t_player *player, t_pickable *pickable)
{
    //if ()
        player->weapons->next->item = pickable->weapon;


}

static void     pick_objects(t_player *player)
{
    t_pickables *pickables;
    t_coords    pick_pos;                                                                                                                                                                               z

    pickables = player->current_sector->pickables;
    pick_pos = (t_coords){pickables->item->object->x, pickables.item->object.y);
    while (pickables.item)
    {
        if (is_close_to(pick_pos, player.pos, 0.2))
            do_stuff(player, pickables.item);
        pickables = pickables->next;
    }
}


static void	init_pickable_from_type(t_pickable *pickable)
{
    if (pickable->type == et_boss)
    {
        pickable->act = boss_intelligence;
        pickable->speed = 0.01;
    }
    else if (pickable->type == et_brazil)
    {
        pickable->act = basic_pickable_intelligence;
        pickable->speed = 0.1;
    }
    else
        error_doom("invalid pickable");
}

/*
**  {.=.}-{.=.}-{.=.}-{.=.}-{.=.}-{.=.}-{.=.}-{.=.}-{.=.}-{.=.}-{.=.}
*/

void    read_pickables_from_file(
        int fd,
        t_textures *textures,
        t_pickables **pickables)
{
    enum e_bool	next;

    if (read(fd, &next, sizeof(next)) <= 0)
        error_doom("The shield has gone mad, Quercus!");
    if (!next)
        return;
    if (!(*pickables = (t_pickables*)malloc(sizeof(t_pickables))))
        error_doom("Couldn't allocate pickables struct");
    (*pickables)->next = NULL;
    read_pickable_from_file(fd, textures, &(*pickables)->item);
    read_pickables_from_file(fd, textures, &(*pickables)->next);
}

void    read_pickable_from_file(int fd, t_textures *textures, t_pickable *pickable)
{
    if (!(pickable->object = (t_object *)malloc(sizeof(t_object))))
        error_doom("Couldn't allocate object in pickable");

    read_object_from_file(fd, textures, pickable->object);

    if (read(fd, &pickable->type, sizeof(pickable->type)) <= 0)
        error_doom("Problem while reading pickable from file");

    init_pickable_from_type(pickable);
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

void    write_pickable_to_file(int fd, t_pickable pickable)
{
    write_object_to_file(fd, *pickable.object);
        error_doom("Problem while reading pickable from file");
    if (write(fd, &pickable.type, sizeof(pickable.type)) <= 0)
        error_doom("Problem while type pickable from file");
}

/*
**  {*+*}-{*+*}-{*+*}-{*+*}-{*+*}-{*+*}-{*+*}-{*+*}-{*+*}-{*+*}-{*+*}
*/

void	add_pickable(
        t_pickables **pickables,
        t_pickables *pickable)
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
        return (previous);
    }
    previous = NULL;
    node = *pickables;
	while (node)
	{
        if (&node->item == pickable)
        {
            previous->next = node->next;
            return (node);
        }
        previous = node;
        node = node->next;
	}
    return NULL;
}

void	delete_pickable(
        t_pickables **pickables,
        t_pickable *pickable)
{
    t_pickables	*node;

    node = extract_pickable(pickables, pickable);
    if (!node)
        return;
    free(node->item.object);
    free(node);
}

void	free_pickables(t_pickables *pickables)
{
    if (!pickables)
        return;
    free_pickables(pickables->next);
    free(pickables->item.object);
    free(pickables);
}
