/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_bool.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfatton <lfatton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 05:44:23 by lfatton           #+#    #+#             */
/*   Updated: 2019/04/12 05:44:54 by lfatton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef E_BOOL_H
# define E_BOOL_H

enum		e_bool
{
    t_false = 0,
    t_true = 1
};

enum e_bool	invert_bool(enum e_bool bool);

#endif
