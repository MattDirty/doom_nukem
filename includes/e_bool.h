/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_bool.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badhont <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 02:44:38 by badhont           #+#    #+#             */
/*   Updated: 2019/04/19 02:45:52 by badhont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOOMNUKEM_E_BOOL_H
# define DOOMNUKEM_E_BOOL_H

enum	e_bool
{
	e_false = 0,
	e_true = 1
};

enum e_bool	invert_bool(enum e_bool bool);

#endif
