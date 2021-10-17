# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mterkhoy <mterkhoy@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/14 20:27:55 by pravry            #+#    #+#              #
#    Updated: 2021/10/17 12:27:37 by mterkhoy         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc

FLAGS = -Wall -Wextra -Werror

NAME = libft.a

INCS_DIR = libft.h

SRCS =  ft_strdup.c\
	   	ft_putchar_fd.c\
		ft_atoi.c\
	   	ft_bzero.c\
	   	ft_calloc.c\
	   	ft_isalnum.c\
	   	ft_isalpha.c\
	   	ft_isascii.c\
	   	ft_isdigit.c\
	   	ft_isprint.c\
	   	ft_itoa.c\
	   	ft_memccpy.c\
	   	ft_memchr.c\
		ft_memcmp.c\
		ft_memcpy.c\
	   	ft_memmove.c\
	   	ft_memset.c\
	   	ft_putendl_fd.c\
	   	ft_putnbr_fd.c\
	   	ft_putstr_fd.c\
	   	ft_split.c\
		ft_split_constraint.c\
	   	ft_strchr.c\
	   	ft_strdup.c\
	   	ft_strjoin.c\
		ft_strcat.c\
	   	ft_strlcat.c\
		ft_strcpy.c\
	   	ft_strlcpy.c\
	   	ft_strlen.c\
	   	ft_strmapi.c\
	   	ft_strncmp.c\
	   	ft_strnstr.c\
	   	ft_strrchr.c\
	   	ft_strtrim.c\
	   	ft_substr.c\
	   	ft_tolower.c\
	   	ft_toupper.c\
		ft_lstlast.c\
		ft_lstsize.c\
		ft_putstr.c\
		ft_strcmp.c\
		ft_lstclear.c\
		ft_lstfree_content.c\
		ft_lstadd_back.c\
		ft_isspace.c\
		ft_tab_join.c\
		ft_atoi_long.c\
		ft_tab_len.c\
		ft_lstnew.c\
		ft_lstsize.c\
		ft_lstlast.c\
		ft_strisnum.c\


HEADERS = $(INCS_DIR)

OBJECT = ${SRCS:.c=.o}


all : $(NAME)

.c.o : 
	${CC} ${FLAGS} -c -I . $< -o ${<:.c=.o}

$(NAME): $(OBJECT)
	ar rc $(NAME) $(OBJECT)
	ranlib $(NAME)

clean:
	@rm -rf $(OBJECT) $(OBJECT_B)

fclean: clean
	@rm -rf $(NAME)

re : fclean all

.PHONY: re clean fclean all bonus
