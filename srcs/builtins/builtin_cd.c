/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mterkhoy <mterkhoy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 11:08:56 by pravry            #+#    #+#             */
/*   Updated: 2022/01/30 19:15:18 by mterkhoy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// CD has to update PWD
	// prolly look at export and unstet and reuse some of those functions

// Prolly needs some securing, especially if we keep the bonus features.

char	*get_path(t_list *env, char *var)
{
	char	*path;

	while (env)
	{
		if (ft_strncmp(var, env->content, 5) == 0)
			path = ft_strjoin(var, ft_strchr(env->content, '=') + 1);	// i would be surprized if secure...
		env = env->next;
	}
	return (path);
}

static void	add_env(char *oldpwd, t_list *env)
{
	while (env)
	{
		if (ft_strncmp(oldpwd, env->content, 6) == 0)
			env->content = ft_strdup(oldpwd);
		env = env->next;
	}
}

static int	update_oldpwd(t_list *env)
{
	char	*oldpwd;
	char	cwd[PATH_MAX];

	if (getcwd(cwd, PATH_MAX) == NULL)
		return (0);
	oldpwd = ft_strjoin("OLDPWD=", cwd);
	if (!oldpwd)
		return (0);
	add_env(oldpwd, env);	// secure this!
	free(oldpwd);
	return (1);
}

static int	go_to_home(t_list *env)
{
	int		ret;
	char	*path;
	char	*tmp;

	update_oldpwd(env);
	path = get_path(env, "HOME=");
	if (!path)
	{
		ft_putstr_fd("cd : HOME not set\n", STDERR_FILENO);
		return (0);
	}
	tmp = ft_strchr(path, '=') + 1;
	ret = chdir(tmp);	// update PWD
	free(path);
	return (ret);
}

static int	go_to_prev(t_list *env)
{
	int		ret;
	char	*path;

	path = get_path(env, "OLDPWD");
	if (!path)
	{
		printf("cd : HOME not set\n");
		return (0);
	}
	update_oldpwd(env);
	ret = chdir(path);	// update PWD
	return (ret);
}

// Technically i think this handles too many options, but i don't see any reason to remove the features so...

int	ft_cd(t_sys *mini, char **args)
{
	int	ret;

	update_oldpwd(mini->env);		// secure? i think we need to return an error if this didnt' work?
	if (!args[1])
		return (go_to_home(mini->env));
	if (ft_strcmp(args[1], "-") == 0)
		ret = go_to_prev(mini->env);
	else
		ret = chdir(args[1]);		// handles . and .. i think, yes, that is correct.
	// update PWD
	return (ret);
}
