#include "doom.h"
#include "timer_handler.h"

void add_event_to_list(
        t_timer_handler *timer_handler,
        t_event *event)
{
    t_event *node;

    if (!timer_handler->first)
        return;

    node = timer_handler->first;

    while(node->next)
        node = node->next;

    node->next = event;
}

void remove_event_from_list(
        t_timer_handler *timer_handler,
        t_event *event)
{
    t_event *node;
    t_event *previous;

    if (!timer_handler->first)
        return;

    node = timer_handler->first;
    previous = NULL;

    while (*node)
    {
        if (node == event)
        {
            if (previous)
                previous->next = node->next;
            else
                timer_handler->first = node->next;
            free(node);
            return;
        }
        previous = node;
        node = node->next;
    }
}

void update_events(t_timer_handler *timer_handler, double ms_since_update)
{
    t_event *node;

    node = timer_handler->first;

    if (!node)
        return;

    while (node)
    {
        node->time_left -= ms_since_update;
        if (node->time_left <= 0)
        {
            node->function(node->params);
            remove_event_from_list(node);
        }
        node = node->next;
    }
}

void add_event(
        t_timer_handler *timer_handler,
        double time_until,
        t_event_func function,
        t_params params)
{
    t_event *new_event;

    if (!(new_event = (t_event*)malloc(sizeof(t_event))))
        error_doom("allocation of t_event failed");

    new_event->time_left = time_until;
    new_event->function = function;
    new_event->params = params;
    new_event->next = NULL;

    add_event_to_list(timer_handler, new_event);
}
