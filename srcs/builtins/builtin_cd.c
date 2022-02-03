/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mterkhoy <mterkhoy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 11:08:56 by pravry            #+#    #+#             */
/*   Updated: 2022/02/03 04:04:42 by me               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


	// returns only the value, not the whole thing!
char	*get_value_of_key(t_list *env, char *key)
{
	char	*value;

//	printf("start of get value of key\n");
	value = NULL;
	while (env)
	{
//		printf("get value of key loop\n");
		if (ft_strncmp(key, env->content, ft_strlen(key)) == 0)
		{
	//		if (((char*)env->content)[ft_strlen(key) + 1] == '=')
	//			value = ft_strjoin(key, ft_strchr(env->content, '=') + 1);
//			printf("get value of key found key, %s, len: %zu\n", key, ft_strlen(key));
			if (((char *)env->content)[ft_strlen(key)] == '=')
			{
				value = ft_strdup(ft_strchr(env->content, '=') + 1);
//				printf("value: %s\n", value);
			}
			return (value);
		}
		// how does join react to receiving a null pointer?
		// i would be surprized if secure...
		env = env->next;
	}
//	printf("end of get value of key\n");
	return (value);
}

// Useless now...
/*
void	add_env(char *oldpwd, t_list *env)
{
	while (env)
	{
		if (ft_strncmp(oldpwd, env->content, 6) == 0)
			env->content = ft_strdup(oldpwd);
		env = env->next;
	}
}
*/

// depricated
/*
int	update_oldpwd(t_list *env)
{
	char	*oldpwd;
	char	cwd[PATH_MAX];

	if (getcwd(cwd, PATH_MAX) == NULL)
		return (0);
	oldpwd = ft_strjoin("OLDPWD=", cwd);
	if (!oldpwd)
		return (0);
	if (!replace_env(env, oldpwd))
	{
		// nothing i think, if in replace env we free the node we should be good?
	}
//	add_env(oldpwd, env);	// secure this!
	free(oldpwd);
	return (1);
}
*/

int	go_to_home(t_list *env)
{
//	int		ret;
	char	*path;
//	char	*tmp;

	path = get_value_of_key(env, "HOME");	// add checks when decide what behavior we want
	go_to_path(env, path);
	ft_scott_free(&path, 1);
	return (0);

/*
	update_oldpwd(env);
	path = find_value_at_key(env, "HOME");
	if (!path)
	{
		ft_putstr_fd("cd : HOME not set\n", STDERR_FILENO);
		return (0);
	}
	tmp = ft_strchr(path, '=') + 1;
	ret = chdir(tmp);	// update PWD
	free(path);
	return (ret);
*/
}

// i want to extract the path from OLDPWD
// then update oldpwd to current PWD
// then change dir and set PWD to current dir, aka 1st oldpwd
int	go_to_prev(t_list *env)
{
//	int		ret;
//	char	*new_pwd_value;
//	char	*new_pwd;
	char	*path;

	path = get_value_of_key(env, "OLDPWD");
	go_to_path(env, path);
	ft_scott_free(&path, 1);
	return (0);

/*
	new_pwd_value = find_value_at_key(env, "OLDPWD");
	if (!new_pwd_value)
	{
		ft_putstr_fd("Error: CD OLDPWD not set\n", 2);
		return (0);
	}
	update_oldpwd(env);
	ret = chdir(new_pwd_value);	// returns 0 on success...
	new_pwd = ft_strjoin("PWD=", new_pwd_value);
	if (!new_pwd)
		return (0);
	if (!replace_env(env, new_pwd))
	{
		if (!add_env_elem(new_pwd, env))	// should i even be doing this?
			return (-1);
	}
	return (ret);
*/
}

// i want to see if i can make it to new path
// if yes update pwd and oldpwd
int	go_to_path(t_list *env, char *path)
{
	int	ret;

	ret = chdir(path);
	if (ret == -1)
		return (1);
//	printf("go to path before update pwds\n");
	update_pwds(env, path);

	return (0);
}


// you good
int	update_pwds(t_list *env, char *new_pwd_path)
{
	char	*new_pwd;
	char	*cur_pwd;
	char	*cur_pwd_path;

//	printf("start of update pwds\n");
	cur_pwd_path = get_value_of_key(env, "PWD");	// need to decide on behavior in case of failure, just move on?
	cur_pwd = ft_strjoin("OLDPWD=", cur_pwd_path);	// what happens when join gets a NULL?
	replace_env(env, cur_pwd);
	ft_scott_free(&cur_pwd_path, 1);
	ft_scott_free(&cur_pwd, 1);

	new_pwd = ft_strjoin("PWD=", new_pwd_path);
	if (!new_pwd)
		return (1);
	replace_env(env, new_pwd);
	ft_scott_free(&new_pwd, 1);
//	printf("end of update pwds\n");
	return (0);
}


// Technically i think this handles too many options, but i don't see any reason to remove the features so...
int	ft_cd(t_sys *mini, char **args)
{
//	int	ret;

//	update_oldpwd(mini->env);	// if we failt to update, we should just keep going...
	if (!args[1])
		return (go_to_home(mini->env));
	else if (ft_strcmp(args[1], "-") == 0)
		return (go_to_prev(mini->env));
	else
		return (go_to_path(mini->env, args[1]));
/*
	if (ft_strcmp(args[1], "-") == 0)
		ret = go_to_prev(mini->env);
	else
	{
		ret = chdir(args[1]);		// handles . and .. i think, yes, that is correct.
		if (ret == 1)	// 1?
			update_pwd(mini->env, args[1]);	// should we be checking if args 1 works?
	}
	return (ret);
*/
	return (0);
}
