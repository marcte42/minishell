/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mterkhoy <mterkhoy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 12:27:18 by pravry            #+#    #+#             */
/*   Updated: 2022/01/29 14:25:12 by me               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

//# include "../libft/libft.h"
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

# define SUCCESS 1
# define ERROR 0

typedef struct		s_sys
{
	int		ret;
	int		exit;
	t_list	*env;
	t_list	*cmds;
}					t_sys;

typedef struct		s_rdr
{
	int     type;
	char    *file;
}					t_rdr;

typedef struct		s_cmd
{
	char	*raw;
	char	**argv;
	char	**clean;
	t_list	*r_in;
	t_list	*r_out;
}					t_cmd;

t_list	*init_env(char **env);
int		init_sys(t_sys *mini, char **env);
int		parse(char *line, t_sys *mini);
char	*parse_env(char *line, t_list *env);
char	**env_to_tab(t_list *env);
int		control_quotes(char *str);
int		is_inquotes(char *s, char *c);
char	*trim_quotes(char *str);
char	*add_space(char *str);

int		exec(t_list *cmds, t_sys *mini);

void	free_sys(t_sys *mini);
void	free_cmds(t_list *cmds);
void	free_env(t_list *env);
void	print_cmds(t_list *cmds);

#endif
