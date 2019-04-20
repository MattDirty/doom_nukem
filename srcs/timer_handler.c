/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timer_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtorsell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/20 02:25:11 by mtorsell          #+#    #+#             */
/*   Updated: 2019/04/20 02:25:15 by mtorsell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "timer_handler.h"

void	timer_handler_init(t_timer_handler *timer_handler)
{
	timer_handler->first = NULL;
	timer_handler->ms_since_update = 0;
	clock_gettime(CLOCK_MONOTONIC_RAW, &timer_handler->time);
}

void	add_event_to_list(
		t_timer_handler *timer_handler,
		t_event *event)
{
	t_event *node;

	if (!timer_handler->first)
	{
		timer_handler->first = event;
		return ;
	}
	node = timer_handler->first;
	while (node->next)
		node = node->next;
	node->next = event;
}

void	remove_event_from_list(
		t_timer_handler *timer_handler,
		t_event *event)
{
	t_event *node;
	t_event *previous;

	if (!timer_handler->first)
		return ;
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
			return ;
		}
		previous = node;
		node = node->next;
	}
}

void	update_events(t_timer_handler *timer_handler)
{
	t_event			*node;
	t_event			*next;
	struct timespec	time;
	double			ms_since_last_call;

	clock_gettime(CLOCK_MONOTONIC_RAW, &time);
	timer_handler->ms_since_update = delta_ms(timer_handler->time, time);
	timer_handler->time = time;
	node = timer_handler->first;
	while (node)
	{
		node->time_left -= timer_handler->ms_since_update;
		next = node->next;
		if (node->time_left <= 0)
		{
			node->time_left = node->interval;
			clock_gettime(CLOCK_MONOTONIC_RAW, &time);
			ms_since_last_call = delta_ms(node->_last_call, time);
			clock_gettime(CLOCK_MONOTONIC_RAW, &node->_last_call);
			if (!node->function(ms_since_last_call, node->params))
				remove_event_from_list(timer_handler, node);
		}
		node = next;
	}
}

void	add_event(
			t_timer_handler *timer_handler,
			double interval,
			t_event_func function,
			t_params params)
{
	t_event *new_event;

	if (!(new_event = (t_event *)malloc(sizeof(t_event))))
		error_doom("allocation of t_event failed");
	new_event->interval = interval;
	new_event->time_left = interval;
	new_event->function = function;
	new_event->params = params;
	new_event->next = NULL;
	clock_gettime(CLOCK_MONOTONIC_RAW, &new_event->_last_call);
	add_event_to_list(timer_handler, new_event);
}
