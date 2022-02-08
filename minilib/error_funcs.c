/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_funcs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ericlazo <erlazo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/24 20:46:56 by ericlazo          #+#    #+#             */
/*   Updated: 2022/02/08 23:55:32 by me               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minilib.h"

long	ft_error_msg(char *str, int ret)
{
	if (!str)
		return (ret);
	ft_putstr(str);
	return (ret);
}

long	ft_error_msg_fd(char *str, int fd, int ret)
{
	if (!str)
		return (ret);
	ft_putstr_fd(str, fd);
	return (ret);
}

long	ft_scott_free(char **str, int ret)
{
	if (str && *str)
	{
		ft_bzero(*str, (int)ft_strlen(*str));
		free(*str);
		*str = NULL;
	}
	return (ret);
}

void	ft_putnbrnl_fd(int nbr, int fd)
{
	ft_putnbr_fd(nbr, fd);
	ft_putchar_fd('\n', fd);
}
