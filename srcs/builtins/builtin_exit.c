/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mterkhoy <mterkhoy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 13:19:25 by pravry            #+#    #+#             */
/*   Updated: 2022/02/02 10:35:38 by mterkhoy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exit(char **args, t_sys *mini)
{
	mini->exit = 1;
	if (args[1] && args[2])
	{
		ft_putstr_fd("minishell : exit: too many arguments\n", STDERR_FILENO);
		return (1);
	}
	if (args[1] && ft_strisnum(args[1]) == 0)
	{
		ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
		ft_putstr_fd(args[1], STDERR_FILENO);
		ft_putendl_fd(": numeric argument required\n", STDERR_FILENO);
		return (255);
	}
	if (!args[1])
		return (0);
	return (ft_atoi(args[1]));
}
