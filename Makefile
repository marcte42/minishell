# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mterkhoy <mterkhoy@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/17 10:25:07 by mterkhoy          #+#    #+#              #
#    Updated: 2022/01/29 16:35:46 by mterkhoy         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC 	= gcc
CFLAGS = -g -Wall -Werror -Wextra

INC_DIR = ./includes
LIB_DIR = ./libft

SRCS =		minishell.c \
			init.c \
			free.c \
			utils.c \
			parse/parse.c \
			parse/parse_env.c \
			parse/parse_quotes.c \
			parse/parse_utils.c \
			exec/exec.c \
			exec/exec_utils.c			

OBJS	= $(addprefix srcs/, $(SRCS:.c=.o))

.c.o:
	$(CC) $(CFLAGS) -I includes -I libft -c $< -o $(<:.c=.o) 

$(NAME): $(OBJS) $(INC_DIR)/minishell.h
		make -s -C $(LIB_DIR)
		$(CC) $(CFLAGS) $(OBJS) -L$(LIB_DIR) -lft -lreadline -o $(NAME)

all: $(NAME)

clean :
	make clean -s -C $(LIB_DIR)
	rm -rf $(OBJS)

fclean:	clean
	$(RM) libft/libft.a
	$(RM) $(NAME)
	$(RM) $(NAME)

re:	fclean all

.PHONY:	all clean fclean re

