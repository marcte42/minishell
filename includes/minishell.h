/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mterkhoy <mterkhoy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 12:27:18 by pravry            #+#    #+#             */
/*   Updated: 2022/02/01 22:07:40 by mterkhoy         ###   ########.fr       */
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
# include <errno.h>

# define SUCCESS 1
# define ERROR 0

typedef struct		s_sys
{
	t_list	*env;			// Liste chainee avec les variables d'env
	t_list	*cmds;			// Liste chainee avec les commandes
	int		cmds_count;		// Nombre de commandes a executer
	int		*pfds;			// Tableau de pipes
	int		retval;			// Valeur finale de retour d'execution
	int		exit;			// Flag pour le builtin exit
}					t_sys;

typedef struct		s_rdr
{
	int     type;			// Type 1 = '<' et '>' type 2 = '<<' et '>>'
	char    *file;			// Destination vers le fichier
}					t_rdr;

typedef struct		s_cmd
{
	int		id;				// L'id dans la ligne de commande 0, 1, 2,...
	pid_t	pid;			// L'id du process de la commande 
	char	*raw;			// Ligne brute	
	char	**argv;			// Tableau de char** avec la commande, les arguments et les redirs
	char	**clean;		// Tableau de char** avec juste la commande et les args
	t_list	*r_in;			// Liste chainee avec toutes les redirections entrantes
	t_list	*r_out;			// Liste chainee avec toutes les redirections sortantes
	int		retval;			// Valeur renvoyee par le process enfant ou le builtin
}					t_cmd;

typedef struct		s_var
{
	int		status;
	int		signal;
	pid_t	pid;
}					t_var;


t_list	*init_env(char **env);
int		init_sys(t_sys *mini, char **env);
int		parse(char *line, t_sys *mini);
char	*parse_env(char *line, t_list *env);
char	*ft_getenv (char *key, t_list *env);
char	*get_key(char *s);
char	**env_to_tab(t_list *env);
int		control_quotes(char *str);
int		is_inquotes(char *s, char *c);
void    trim_quotes(char *str);
char	*add_space(char *str);
void	print_list(t_list *cmds);

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
int		ft_env(t_sys *mini, int fd);

int		update_pwds(t_list *env, char *new_pwd_path);
int		go_to_path(t_list *env, char *path);
int		replace_env(t_list *env, char *args);
int		add_env_elem(char *arg, t_list *env);
int		ft_export(char	**args, t_list *env, int fd);

int		ft_unset(char **args, t_list *env);
int		ft_exit(char **args, t_sys *mini);

void	free_sys(t_sys *mini);
void	reset_free_sys(t_sys *mini);
void	print_cmds(t_list *cmds);

void	signal_handler(int sig);
void	signal_handler_2(int sig);

int		is_dir(char *path);
int		is_valid_file(char *file);

#endif
