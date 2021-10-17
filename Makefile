# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mterkhoy <mterkhoy@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/17 10:25:07 by mterkhoy          #+#    #+#              #
#    Updated: 2021/10/17 16:11:22 by mterkhoy         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC 	= clang-9
CFLAGS = -Wall -Wextra -Werror

INC_DIR = ./includes
LIB_DIR = ./libft

SRCS =		minishell.c \
			init.c \
			parser/parse.c \
			parser/env.c \
			parser/quotes.c \
			parser/utils.c \
			executor/exec.c \
			executor/utils.c \
			utils.c

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
