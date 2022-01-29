/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minilib.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ericlazo <erlazo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 19:33:21 by ericlazo          #+#    #+#             */
/*   Updated: 2022/01/29 14:07:36 by me               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINILIB_H
# define MINILIB_H

# include <unistd.h>
# include <stdlib.h>
# include <string.h>

# include "libft.h"

typedef struct s_nlist
{
	int				index;
	void			*content;
	struct s_nlist	*next;
}				t_nlist;

typedef struct s_ilist
{
	int				num;
	struct s_ilist	*next;
}				t_ilist;

/*
**		GNL
*/

int			ft_gnl(char **line, int fd);

/*
**		GNL Utils
*/

size_t		ft_sstrlen(const char *s);
int			ft_sfindchar(char *str, char c);
int			ft_ibzero(void *s, size_t n);

/*
**		List Funcs More
*/

int			ft_print_full_list(t_list *lst);
void		ft_lstdel_str_elem(void *data);

/*
**		nList Funcs
*/

int			ft_nlstadd_back(t_nlist **lst, t_nlist *new);
int			ft_nlstadd_front(t_nlist **lst, t_nlist *new);
t_nlist		*ft_nlstnew(void *content, int index);
int			ft_nlstdel_all(t_nlist **lst);

/*
**		iList Funcs
*/

t_ilist		*ft_ilstnew(int num);
int			ft_ilstadd_back(t_ilist **lst, t_ilist *new);
int			ft_ilstadd_front(t_ilist **lst, t_ilist *new);
int			ft_ilstdel_all(t_ilist **lst);


/*
**		Stand Alone nList Funcs
*/

int			ft_nlstdel_n_one(t_nlist **lst, int n);

/*
**		Str Funcs
*/

int			ft_findchar(char *str, char c);

/*
**		Error Funcs
*/

long		ft_error_msg(char *str, int ret);
long		ft_error_msg_fd(char *str, int fd, int ret);
long		ft_scott_free(char **str, int ret);

/*
**		Tab Funcs
*/

int			ft_free_strtab(char **tab);
int			ft_print_strtab(char **tab);

/*
**		Is Functions
*/

int			ft_str_isdigit(char *str);
int			ft_str_isprint(char *str);

#endif
