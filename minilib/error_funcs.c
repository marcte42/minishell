/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_funcs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acousini <acousini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 18:44:34 by acousini          #+#    #+#             */
/*   Updated: 2022/03/02 18:53:55 by acousini         ###   ########.fr       */
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
