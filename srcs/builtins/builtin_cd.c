/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pravry <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 11:08:56 by pravry            #+#    #+#             */
/*   Updated: 2021/06/28 10:30:42 by pravry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_path(t_envi *env, char *var)
{
	char	*path;
	
	while (env)
	{
		if (ft_strncmp(var, env->value, 5) == 0)
			path = ft_strjoin(var, copy_value(env->value));
		env = env->next;
	}
	return (path);
}

static void	add_env(char *oldpwd, t_envi *env)
{
	while (env)
	{
		if (ft_strncmp(oldpwd, env->value, 6) == 0)
			env->value = ft_strdup(oldpwd);
		env = env->next;
	}
}

static int	update_oldpwd(t_envi *env)
{
	char	*oldpwd;
	char	cwd[PATH_MAX];

	if (getcwd(cwd, PATH_MAX) == NULL)
		return (0);
	if (!(oldpwd = ft_strjoin("OLDPWD=", cwd)))
		return (0);
	add_env(oldpwd, env);
	free(oldpwd);
	return (1);
}

static int	go_to_home(t_envi *env)
{
	int	ret;
	char	*path;
	char	*tmp;

	update_oldpwd(env);
	path = get_path(env, "HOME=");
	if (!path)
	{
		printf("cd : HOME not set\n");
		return (0);
	}
	tmp = copy_value(path);
	ret = chdir(tmp);
	free(path);
	free(tmp);
	return (ret);
}

static int	go_to_prev(t_envi *env)
{
	int	ret;
	char *path;

	path = get_path(env, "OLDPWD");
	if (!path)
    {
        printf("cd : HOME not set\n");
        return (0);
    }
	update_oldpwd(env);
	ret = chdir(path);
	return (ret);
}

int		ft_cd(char **args, t_envi *env)
{
	int ret;

	update_oldpwd(env);
	if (!args[1])
		return (go_to_home(env));
	if (ft_strcmp(args[1], "-") == 0)
		ret = go_to_prev(env);
	else
		ret = chdir(args[1]);
	return (ret);
}
