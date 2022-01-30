/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mterkhoy <mterkhoy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 21:19:11 by pravry            #+#    #+#             */
/*   Updated: 2022/01/30 16:38:11 by mterkhoy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(t_sys *mini, int fd)
{
	t_list	*tmp;

	tmp = mini->env;
	while (tmp)
	{
		ft_putstr_fd(tmp->content, fd);
		ft_putchar_fd('\n', fd);
		tmp = tmp->next;
	}
	return (SUCCESS);
}
