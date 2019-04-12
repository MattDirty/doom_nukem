/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfatton <lfatton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 06:09:24 by lfatton           #+#    #+#             */
/*   Updated: 2019/04/12 06:09:26 by lfatton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <time.h>

double delta_ms(struct timespec start, struct timespec end)
{
    return (((end.tv_sec - start.tv_sec) * 1e+9
           + (end.tv_nsec - start.tv_nsec)) * 1e-6);
}
