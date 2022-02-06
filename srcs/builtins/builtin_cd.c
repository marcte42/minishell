/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me <erlazo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 00:30:06 by me                #+#    #+#             */
/*   Updated: 2022/02/06 22:48:07 by me               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	go_to_home(t_list *env)
{
	char	*path;

	path = get_value_of_key(env, "HOME");
	if (!path)
	{
		return (ft_error_msg_fd("Error: cd HOME not set\n", 2, 1));
	}
	go_to_path(env, path);
	ft_scott_free(&path, 1);
	return (0);
}

int	go_to_prev(t_list *env)
{
	char	*path;

	path = get_value_of_key(env, "OLDPWD");
	if (!path)
	{
		return (ft_error_msg_fd("Error: cd OLDPWD not set\n", 2, 1));
	}
	go_to_path(env, path);
	ft_scott_free(&path, 1);
	return (0);
}

int	go_to_path(t_list *env, char *path)
{
	int		ret;
	char	you_are_here[PATH_MAX];

	ret = chdir(path);
	if (ret == -1)
		return (1);	// some error message?
	if (getcwd(you_are_here, PATH_MAX) == NULL)
		return (1);	// another error message?
	update_pwds(env, you_are_here);
	return (0);
}

int	update_pwds(t_list *env, char *new_pwd_path)
{
	char	*new_pwd;
	char	*cur_pwd;
	char	*cur_pwd_path;

	cur_pwd_path = get_value_of_key(env, "PWD");
	cur_pwd = ft_mstrjoin("OLDPWD=", cur_pwd_path);
	//cur_pwd = NULL;
	// do the check before replace?
	replace_env(env, cur_pwd);
	ft_scott_free(&cur_pwd_path, 1);
	ft_scott_free(&cur_pwd, 1);
	new_pwd = ft_mstrjoin("PWD=", new_pwd_path);
	if (!new_pwd)	// seems unnecessary, replace env checks if input is not NULL, if it is it stops, same as doing a check here
		return (1);
	replace_env(env, new_pwd);
	ft_scott_free(&new_pwd, 1);
	return (0);
}

// Technically i think this handles too many options, but i don't see any reason to remove the features so...
int	ft_cd(t_sys *mini, char **args)
{
	if (!args[1])
		return (go_to_home(mini->env));
	else if (ft_strcmp(args[1], "-") == 0)
		return (go_to_prev(mini->env));
	else
		return (go_to_path(mini->env, args[1]));
	return (0);
}
