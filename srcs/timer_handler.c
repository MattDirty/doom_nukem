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
    t_event *n;

    if (!timer_handler->first)
    {
        timer_handler->first = event;
        return;
    }

    n = timer_handler->first;

    while(n->next)
        n = n->next;

    n->next = event;
}

void remove_event_from_list(
        t_timer_handler *timer_handler,
        t_event *event)
{
    t_event *n;
    t_event *previous;

    if (!timer_handler->first)
        return;
    n = timer_handler->first;
    previous = NULL;
    while (n)
    {
        if (n == event)
        {
            if (previous)
                previous->next = n->next;
            else
                timer_handler->first = n->next;
            free(n);
            return;
        }
        previous = n;
        n = n->next;
    }
}

void update_events(t_timer_handler *timer_handler)
{
    t_event *n;
    t_event *next;
    struct timespec time;
    double ms_since_last_call;

    clock_gettime(CLOCK_MONOTONIC_RAW, &time);
	timer_handler->ms_since_update = delta_ms(timer_handler->time, time);
    timer_handler->time = time;
    n = timer_handler->first;
    while (n)
    {
		n->time_left -= timer_handler->ms_since_update;
		next = n->next;
        if (n->time_left <= 0)
        {
            n->time_left = n->interval;
            clock_gettime(CLOCK_MONOTONIC_RAW, &time);
            ms_since_last_call = delta_ms(n->_last_call, time);
            clock_gettime(CLOCK_MONOTONIC_RAW, &n->_last_call);
            if (!n->function(ms_since_last_call, n->params))
                remove_event_from_list(timer_handler, n);
        }
        n = next;
    }
}

void add_event(
        t_timer_handler *timer_handler,
        double interval,
        t_event_func function,
        t_params params)
{
    t_event *new_event;

    if (!(new_event = (t_event*)malloc(sizeof(t_event))))
        error_doom("allocation of t_event failed");

    new_event->interval = interval;
    new_event->time_left = interval;
    new_event->function = function;
    new_event->params = params;
    new_event->next = NULL;
    clock_gettime(CLOCK_MONOTONIC_RAW, &new_event->_last_call);

    add_event_to_list(timer_handler, new_event);
}
