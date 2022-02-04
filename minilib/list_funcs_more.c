/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_funcs_more.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me <erlazo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 20:41:51 by me                #+#    #+#             */
/*   Updated: 2022/01/19 05:47:13 by me               ###   ########.fr       */
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
	free((char*)data);
}

t_list	*ft_lstdup(t_list *lst)
{
	t_list *nlist;
	t_list	*new;

	nlist = NULL;
	while (lst)
	{
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

t_list	*generate_list(char *str)
{
	t_list	*new;
	t_list	*ret;
	int		i;
	char	**tab;

	ret = NULL;
	tab = ft_split(str, ' ');
	i = 0;
	while (tab[i])
	{
		new = ft_lstnew(tab[i]);
		if (!new)
		{
			ft_lstclear(&ret, free);
			return (NULL);
		}
		ft_lstadd_back(&ret, new);
		++i;
	}
	free(tab);
	return (ret);
}