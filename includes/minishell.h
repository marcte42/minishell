/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mterkhoy <mterkhoy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 16:07:04 by mterkhoy          #+#    #+#             */
/*   Updated: 2022/02/10 21:33:14 by mterkhoy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include "minilib.h"

# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <stddef.h>
# include <stdio.h>
# include <limits.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <errno.h>

# define SUCCESS 1
# define ERROR 0

typedef struct s_sys
{
	char	*line;
	t_list	*env;
	t_list	*cmds;
	int		cmds_count;
	int		*pfds;
	int		retval;
	int		exit;
}					t_sys;

typedef struct s_rdr
{
	int		type;
	char	*file;
}					t_rdr;

typedef struct s_cmd
{
	int		id;
	pid_t	pid;
	char	*raw;
	char	**argv;
	char	**clean;
	t_list	*r_in;
	t_list	*r_out;
	int		fd_in;
	int		fd_out;
	int		retval;
}					t_cmd;

t_list	*init_env(char **env);
int		init_sys(t_sys *mini, char **env);
int		parse(t_sys *mini);
t_list	*parse_pipes(char *line);
char	*parse_env(t_sys *mini, char *line, t_list *env);
char	*parse_env_heredoc(t_sys *mini, char *line, t_list *env);
char	*ft_getenv(t_sys *mini, char *key, t_list *env);
int		parse_redirects(t_sys *mini, t_cmd *cmd, int i, int j);
int		handle_heredoc(t_sys *mini, t_rdr *rdr, char **argv, int id);
char	*get_key(char *s);
char	**env_to_tab(t_list *env);
int		control_quotes(char *str);
int		is_inquotes(char *s, char *c);
int		has_quotes(char *s);
void	trim_quotes(char *str);
char	*add_space(char *str);
void	print_list(t_list *cmds);

int		ft_has_valid_env(t_sys *mini, char *line, int i);
int		special_mini_error(char *file, int ret);

int		exec(t_sys *mini);
int		init_pfds(t_sys *mini);
int		close_pfds(t_sys *mini);

/*
**		Builtins
*/

int		is_builtin(char *cmd);
int		exec_builtin(t_sys *mini, t_cmd *cmd);
int		ft_echo(char **args, int fd);
int		ft_cd(t_sys *mini, char **args);
int		ft_pwd(int fd);

int		check_valid_env(char *env);
char	*get_value_of_key(t_list *env, char *key);
int		replace_env(t_list *env, char *args);
int		ft_env(t_sys *mini, int fd);

int		update_pwds(t_list *env, char *new_pwd_path);
int		go_to_path(t_list *env, char *path);
int		replace_env(t_list *env, char *args);
int		add_env_elem(char *arg, t_list *env);
int		ft_export(char	**args, t_list *env, int fd);

int		ft_unset(char **args, t_list **env);
int		ft_exit(char **args, t_sys *mini);

void	free_sys(t_sys *mini);
void	reset_free_sys(t_sys *mini);
void	print_cmds(t_list *cmds);

void	signal_handler(int sig);
void	signal_handler_2(int sig);

int		is_dir(char *path);
int		ft_isempty(char *s);
int		count_pipes(char *s);
int		is_binary(char *file);
int		get_fd_in(t_sys *mini, t_cmd *cmd);
int		get_fd_out(t_sys *mini, t_cmd *cmd);
void	minishell_error(char *file);

#endif
