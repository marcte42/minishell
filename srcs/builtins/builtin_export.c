/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mterkhoy <mterkhoy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 21:19:56 by me                #+#    #+#             */
/*   Updated: 2022/02/07 19:22:44 by mterkhoy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	add_env_elem(char *arg, t_list *env)
{
	t_list	*node;
	char	*tmp;

	tmp = ft_strdup(arg);
	if (!tmp)
		return (ERROR);
	node = ft_lstnew(tmp);
	if (!node)
	{
		free(tmp);
		return (ERROR);
	}
	ft_lstadd_back(&env, node);
	return (SUCCESS);
}

t_list	*sort_t_list(t_list *lst)
{
	t_list	*ret;
	t_list	*next;
	t_list	*first;
	char	*tmp;

	if (!lst)
		return (NULL);
	ret = ft_lstdup(lst);
	first = ret;
	while (ret && ret->next)
	{
		next = ret->next;
		if (ft_strcmp(ret->content, next->content) > 0)
		{
			tmp = ret->content;
			ret->content = next->content;
			next->content = tmp;
			ret = first;
		}
		else
			ret = ret->next;
	}
	return (first);
}

int	print_envs(t_list *env, int fd)
{
	t_list	*tmp;
	t_list	*first;
	char	*key;

	tmp = sort_t_list(env);
	first = tmp;
	while (tmp)
	{
		key = get_key(tmp->content);
		if (!key)
			return (ft_lstdel_elems(&first, 1));
		ft_putstr_fd("declare -x ", fd);
		ft_putstr_fd(key, fd);
		if (ft_strlen(tmp->content) > ft_strlen(key))
		{
			ft_putstr_fd("=\"", fd);
			ft_putstr_fd(&((char *)tmp->content)[ft_strlen(key) + 1], fd);
			ft_putstr_fd("\"", fd);
		}
		ft_putstr_fd("\n", fd);
		free(key);
		tmp = tmp->next;
	}
	return (ft_lstdel_elems(&first, 0));
}

int	ft_export(char **args, t_list *env, int fd)
{
	int	ret;
	int	i;

	ret = 0;
	if (!args[1])
		return (print_envs(env, fd));
	else
	{
		i = 0;
		while (args[++i])
		{
			if (!check_valid_env(args[i]))
			{
				ret = 1;
				ft_putstr_fd("Error: Export \'", 2);
				ft_putstr_fd(args[i], 2);
				ft_putstr_fd("\' not a valid identifier\n", 2);
				continue ;
			}
			if (!replace_env(env, args[i]) && !add_env_elem(args[i], env))
				ret = 1;
		}
	}
	return (ret);
}
