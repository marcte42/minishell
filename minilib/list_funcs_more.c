/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_funcs_more.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me <erlazo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 20:41:51 by me                #+#    #+#             */
/*   Updated: 2022/02/08 23:54:41 by me               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minilib.h"

void	ft_print_list_elem(t_list *elem)
{
	ft_putstr((char *)elem->content);
	ft_putchar_fd('\n', 1);
}

int	ft_print_full_list(t_list *lst)
{
	if (!lst)
		return (0);
	while (lst)
	{
		ft_print_list_elem(lst);
		lst = lst->next;
	}
	return (1);
}

void	ft_lstdel_str_elem(void *data)
{
	if (!data)
		return ;
	free((char *)data);
}

t_list	*ft_lstdup(t_list *lst)
{
	t_list	*nlist;
	t_list	*new;
	char	*str;

	nlist = NULL;
	str = NULL;
	while (lst)
	{
/*		str = ft_strdup(lst->content);
		if (!str)
		{
			ft_lstclear(&nlist, free);
			return (NULL);
		}
*/
//		new = ft_lstnew(str);
		new = ft_lstnew(lst->content);
		if (!new)
		{
			ft_lstclear(&nlist, free);
			return (NULL);
		}
		ft_lstadd_back(&nlist, new);
		lst = lst->next;
	}
	return (nlist);
}

int	ft_lstdel_elems(t_list **lst, int ret)
{
	t_list *tmp;

	if (!lst || !*lst)
		return (ret);
	while (*lst)
	{
		tmp = (*lst)->next;
		(*lst)->content = NULL;
		free(*lst);
		*lst = tmp;
	}
	return (ret);
}
