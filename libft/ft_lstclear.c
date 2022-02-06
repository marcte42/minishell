/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mterkhoy <mterkhoy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 18:07:19 by pravry            #+#    #+#             */
/*   Updated: 2021/12/19 21:10:28 by mterkhoy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*free_lst;

	while (*lst)
	{
		free_lst = *lst;
		(*del)(free_lst->content);
		*lst = (*lst)->next;
		free(free_lst);
	}
	*lst = NULL;
}
