/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mterkhoy <mterkhoy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 21:19:11 by pravry            #+#    #+#             */
/*   Updated: 2022/01/30 16:38:37 by mterkhoy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// looks fine to me

int	ft_pwd(int fd)
{
	char	cwd[PATH_MAX];	// doesn't get allocated so i think all good

	if (getcwd(cwd, PATH_MAX))
	{
		ft_putstr_fd(cwd, fd);		// make sure you understand what effect a new fd from the builtin redirects could have
		ft_putchar_fd('\n', fd);
		return (SUCCESS);
	}
	return (ERROR);
}
