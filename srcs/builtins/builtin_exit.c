/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mterkhoy <mterkhoy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 13:19:25 by pravry            #+#    #+#             */
/*   Updated: 2022/02/06 22:01:58 by mterkhoy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_full_strisnum(const char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (0);
	if (str[0] == '-' || str[0] == '+')
		i++;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	ft_exit(char **args, t_sys *mini)
{
	if (args[1] && args[2])
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", STDERR_FILENO);
		return (1);
	}
	if (mini->cmds_count == 1)
		mini->exit = 1;
	if (args[1] && ft_full_strisnum(args[1]) == 0)
	{
		ft_putstr_fd("exit\n", STDERR_FILENO);
		ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
		ft_putstr_fd(args[1], STDERR_FILENO);
		ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
		return (2);
	}
	if (!args[1])
		return (0);
	return (ft_atoi(args[1]));
}
