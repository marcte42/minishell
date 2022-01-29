/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mterkhoy <mterkhoy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 12:27:18 by pravry            #+#    #+#             */
/*   Updated: 2022/01/29 16:37:50 by mterkhoy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

//# include "../libft/libft.h"
# include "libft.h"

// # include "minilib.h"

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
	t_list	*env;			// Liste chainee avec les variables d'env
	t_list	*cmds;			// Liste chainee avec les commandes
	int		cmds_count;		// Nombre de commandes a executer
	int		*pfds;			// Tableau de pipes
	int		status;			// Valeur finale de retour d'execution
	int		exit;			// ???
}					t_sys;

typedef struct		s_rdr
{
	int     type;			// Type 1 = '<' et '>' type 2 = '<<' et '>>'
	char    *file;			// Destination vers le fichier
}					t_rdr;

typedef struct		s_cmd
{
	pid_t	pid;			// L'id du process de la commande 
	char	*raw;			// Ligne brute	
	char	**argv;			// Tableau de char** avec la commande, les arguments et les redirs
	char	**clean;		// Tableau de char** avec juste la commande et les args
	t_list	*r_in;			// Liste chainee avec toutes les redirections entrantes
	t_list	*r_out;			// Liste chainee avec toutes les redirections sortantes
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
int		init_pfds(t_sys *mini);
int		close_pfds(t_sys *mini);

void	free_sys(t_sys *mini);
void	free_cmds(t_list *cmds);
void	free_env(t_list *env);
void	print_cmds(t_list *cmds);

#endif
