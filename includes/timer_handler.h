#ifndef TIMER_HANDLER_H
# define TIMER_HANDLER_H

# include "e_bool.h"

typedef const void *t_params;
/*
 * t_event_func returns a boolean that tells the
 * handler if the event must be destroyed or if it
 * needs to keep calling it.
 * Return t_false to destroy the event.
 * Return t_true to recall the event after interval ms.
 */
typedef enum e_bool (*t_event_func)(double ms_since_update, t_params);

typedef struct    s_event
{
    double interval;
	double time_left;
    t_event_func function;
    t_params params;
    struct s_event *next;
	struct timespec _last_call;
} t_event;

typedef struct    s_timer_handler
{
	t_event	*first;
	double	ms_since_update;
	struct timespec time;
} t_timer_handler;

void timer_handler_init(t_timer_handler *timer_handler);
void remove_event_from_list(t_timer_handler *timer_handler, t_event *event);
void update_events(t_timer_handler *timer_handler);
void add_event(
        t_timer_handler *timer_handler,
        double interval,
        t_event_func function,
        t_params params);

#endif
