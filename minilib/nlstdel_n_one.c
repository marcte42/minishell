/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nlstdel_n_one.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acousini <acousini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 18:45:59 by acousini          #+#    #+#             */
/*   Updated: 2022/03/02 18:53:55 by acousini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minilib.h"

void	n_is_zero(t_nlist **lst)
{
	t_nlist	*tmp;

	tmp = (*lst)->next;
	free((*lst)->content);
	free(*lst);
	*lst = tmp;
}

int	ft_nlstdel_n_one(t_nlist **lst, int n)
{
	t_nlist	*tmp;
	t_nlist	*elem;

	if (!lst || !*lst || n < 0)
		return (0);
	tmp = NULL;
	if (n == 0)
		n_is_zero(lst);
	else
	{
		tmp = *lst;
		while (tmp && tmp->index < n - 1)
			tmp = tmp->next;
		elem = tmp->next;
		free(elem->content);
		tmp->next = elem->next;
		free(elem);
		tmp = tmp->next;
	}
	while (tmp)
	{
		tmp->index -= 1;
		tmp = tmp->next;
	}
	return (1);
}
