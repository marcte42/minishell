/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ilist_funcs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acousini <acousini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 18:45:35 by acousini          #+#    #+#             */
/*   Updated: 2022/03/02 18:53:55 by acousini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minilib.h"

t_ilist	*ft_ilstnew(int num)
{
	t_ilist	*elem;

	elem = (t_ilist *)malloc(sizeof(t_ilist));
	if (!elem)
		return (NULL);
	elem->num = num;
	elem->next = NULL;
	return (elem);
}

int	ft_ilstadd_back(t_ilist **lst, t_ilist *new)
{
	t_ilist	*tmp;

	if (!lst || !new)
		return (0);
	if (!*lst)
	{
		*lst = new;
		return (1);
	}
	tmp = *lst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	new->next = NULL;
	return (1);
}

int	ft_ilstadd_front(t_ilist **lst, t_ilist *new)
{
	if (!lst || !new)
		return (0);
	new->next = *lst;
	*lst = new;
	return (1);
}

int	ft_ilstdel_all(t_ilist **lst)
{
	t_ilist	*tmp;

	if (!lst)
		return (0);
	tmp = *lst;
	while (*lst)
	{
		tmp = (*lst)->next;
		free(*lst);
		*lst = tmp;
	}
	return (1);
}
