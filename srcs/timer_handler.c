#include "doom.h"
#include "timer_handler.h"

void timer_handler_init(t_timer_handler *timer_handler)
{
	timer_handler->first = NULL;
	timer_handler->ms_since_update = 0;
	clock_gettime(CLOCK_MONOTONIC_RAW, &timer_handler->time);
}

void add_event_to_list(
        t_timer_handler *timer_handler,
        t_event *event)
{
    t_event *node;

    if (!timer_handler->first)
    {
        timer_handler->first = event;
        return;
    }

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

    while (node)
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

void update_events(t_timer_handler *timer_handler)
{
    t_event *node;
    struct timespec time;

    clock_gettime(CLOCK_MONOTONIC_RAW, &time);
	timer_handler->ms_since_update = delta_ms(timer_handler->time, time);
    timer_handler->time = time;

    node = timer_handler->first;

    while (node)
    {
		node->time_left -= timer_handler->ms_since_update;
        if (node->time_left <= 0)
        {
            node->function(node->params);
            node->time_left = node->interval;
            if (node->destroy_after_call)
                remove_event_from_list(timer_handler, node);
        }
        node = node->next;
    }
}

void add_event(
        t_timer_handler *timer_handler,
        double interval,
        enum e_bool destroy_after_call,
        t_event_func function,
        t_params params)
{
    t_event *new_event;

    if (!(new_event = (t_event*)malloc(sizeof(t_event))))
        error_doom("allocation of t_event failed");

    new_event->interval = interval;
    new_event->time_left = interval;
    new_event->destroy_after_call = destroy_after_call;
    new_event->function = function;
    new_event->params = params;
    new_event->next = NULL;

    add_event_to_list(timer_handler, new_event);
}
