/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mterkhoy <mterkhoy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 22:37:23 by me                #+#    #+#             */
/*   Updated: 2022/02/10 20:31:11 by mterkhoy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	size_arg(char **args)
{
	int	size;

	size = 0;
	while (args[size])
		size++;
	return (size);
}

int	is_flag(char *str)
{
	int	i;

	if (!str)
		return (0);
	if (str[0] != '-')
		return (0);
	i = 1;
	while (str[++i])
		if (str[i] != 'n')
			return (0);
	return (1);
}

int	ft_echo(char **args, int fd)
{
	int	i;
	int	flag;

	i = 1;
	flag = 0;
	if (size_arg(args) > 1)
	{
		while (args[i] && is_flag(args[i]))
		{
			flag = 1;
			i++;
		}
		while (args[i])
		{
			ft_putstr_fd(args[i], fd);
			if (args[i + 1])
				ft_putchar_fd(' ', fd);
			i++;
		}
	}
	if (flag == 0)
		ft_putchar_fd('\n', fd);
	return (0);
}
