/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timer_handler.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badhont <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 10:07:03 by badhont           #+#    #+#             */
/*   Updated: 2019/04/19 10:12:44 by badhont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TIMER_HANDLER_H
# define TIMER_HANDLER_H

# include "time.h"
# include "e_bool.h"
# include <time.h>

typedef const void *t_params;

typedef enum e_bool	(*t_event_func)(double ms_since_update, t_params);

typedef struct			s_event
{
	double				interval;
	double				time_left;
	t_event_func		function;
	t_params			params;
	struct s_event		*next;
	struct timespec		last_call;
}						t_event;

typedef struct			s_timer_handler
{
	t_event				*first;
	double				ms_since_update;
	struct timespec		time;
}						t_timer_handler;

void					timer_handler_init(
							t_timer_handler *timer_handler);
void					remove_event_from_list(t_timer_handler *timer_handler,
							t_event *event);
void					update_events(t_timer_handler *timer_handler);
void					add_event(t_timer_handler *timer_handler,
							double interval, t_event_func function,
							t_params params);

#endif
