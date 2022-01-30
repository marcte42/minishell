/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mterkhoy <mterkhoy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 11:08:56 by pravry            #+#    #+#             */
/*   Updated: 2022/01/30 14:35:07 by mterkhoy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_path(t_list *env, char *var)
{
	char	*path;
	
	while (env)
	{
		if (ft_strncmp(var, env->content, 5) == 0)
			path = ft_strjoin(var, ft_strchr(env->content, '=') + 1);
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
	if (!(oldpwd = ft_strjoin("OLDPWD=", cwd)))
		return (0);
	add_env(oldpwd, env);
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
		printf("cd : HOME not set\n");
		return (0);
	}
	tmp = ft_strchr(path, '=') + 1;
	ret = chdir(tmp);
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
	ret = chdir(path);
	return (ret);
}

int		ft_cd(t_sys *mini, char **args)
{
	int ret;

	update_oldpwd(mini->env);
	if (!args[1])
		return (go_to_home(mini->env));
	if (ft_strcmp(args[1], "-") == 0)
		ret = go_to_prev(mini->env);
	else
		ret = chdir(args[1]);
	return (ret);
}
