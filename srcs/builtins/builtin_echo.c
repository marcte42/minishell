/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mterkhoy <mterkhoy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 22:37:23 by me                #+#    #+#             */
/*   Updated: 2022/02/09 23:56:20 by me               ###   ########.fr       */
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

int	print_arg(char *arg, int fd)
{
	int		i;
	char	**line;

	line = ft_split(arg, ' ');
	if (!line)
		return (0);
	i = 0;
	while (line[i])
	{
		ft_putstr_fd(line[i], fd);
		if (line[i + 1])
			ft_putchar_fd(' ', fd);
		++i;
	}
	ft_free_strtab(line);
	free(line);
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
		while (args[i] && ft_strcmp(args[i], "-n") == 0)
		{
			flag = 1;
			i++;
		}
		while (args[i])
		{
			print_arg(args[i], fd);
			if (args[i + 1])
				ft_putchar_fd(' ', fd);
			i++;
		}
	}
	if (flag == 0)
		ft_putchar_fd('\n', fd);
	return (0);
}
