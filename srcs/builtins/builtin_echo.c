/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mterkhoy <mterkhoy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 17:47:33 by pravry            #+#    #+#             */
/*   Updated: 2022/01/30 16:42:15 by mterkhoy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// seems good to me...

// BUt there is a double free somewhere when we echo $HOME or any env var...

int	size_arg(char **args)
{
	int	size;

	size = 0;
	while (args[size])
		size++;
	return (size);
}

int	ft_echo(char **args, int fd)
{
	int	i;
	int	flag;

	i = 1;
	flag = 0;
	if (size_arg(args) > 1)
	{
		while (args[i] && ft_strcmp(args[i], "-n") == 0)
		{
			flag = 1;
			i++;
		}
		while (args[i])	// do we maybe want to reset i to 1 and skip if args[i] == "-n" ? NO -n only works in first possition
		{
			ft_putstr_fd(args[i], fd);
			if (args[i + 1] && args[i][0] != '\0')
				ft_putchar_fd(' ', fd);
			i++;
		}
	}
	if (flag == 0)
		ft_putchar_fd('\n', fd);
	return (SUCCESS);
}
