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

void	*ft_lstdel_elems(t_list **lst)
{
	t_list *tmp;

	if (!lst || !*lst)
		return (NULL);
	while (*lst)
	{
		tmp = (*lst)->next;
		free(*lst);
		*lst = tmp;
	}
	return (NULL);
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
