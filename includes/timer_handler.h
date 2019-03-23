#ifndef DOOM_NUKEM_TIMER_HANDLER_H
# define DOOM_NUKEM_TIMER_HANDLER_H

typedef const void *const t_params;
typedef void (*t_event_func)(t_params);

typedef struct    s_event
{
    double time_left;
    t_event_func function;
    t_params params;
    struct s_event *next;
} t_event;

typedef struct    s_timer_handler
{
    t_event *first;
} t_timer_handler;

void update_events(t_timer_handler *timer_handler, double ms_since_update);
void add_event(
        t_timer_handler *timer_handler,
        double time_until,
        t_event_func function,
        t_params params);

#endif //DOOM_NUKEM_TIMER_HANDLER_H
