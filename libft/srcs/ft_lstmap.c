/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfatton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/25 17:45:14 by lfatton           #+#    #+#             */
/*   Updated: 2018/05/07 15:50:53 by lfatton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*new;
	t_list	*start;

	if (lst && f)
	{
		new = f(lst);
		start = new;
		lst = lst->next;
		while (lst)
		{
			ft_lstradd(&new, f(lst));
			lst = lst->next;
		}
		return (start);
	}
	return (NULL);
}
