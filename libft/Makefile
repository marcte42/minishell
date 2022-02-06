# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mterkhoy <mterkhoy@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/14 20:27:55 by pravry            #+#    #+#              #
#    Updated: 2022/02/06 19:09:01 by mterkhoy         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc

FLAGS = -Wall -Wextra -Werror

NAME = libft.a

DIR_SRCS	=	./
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


#INCS_DIR = libft.h

DIR_INC		=	./
INCS		=	-I$(DIR_INC)

CFLAGS		=	$(FLAGS) $(INCS)

HEADERS = $(INCS_DIR)

DIR_OBJ		=	./objs/

OBJ_ALL		=	$(SRCS:.c=.o)

OBJS_ALL	=	$(addprefix $(DIR_OBJ),$(OBJ_ALL))





#OBJECT = ${SRCS:.c=.o}


all : $(NAME)

#.c.o : 
#	${CC} ${FLAGS} -c -I . $< -o ${<:.c=.o}

#$(NAME): $(OBJECT)
#	ar rc $(NAME) $(OBJECT)
#	ranlib $(NAME)

$(NAME): $(OBJS_ALL)
	ar rc $(NAME) $(OBJS_ALL)
	ranlib $(NAME)
	printf "$(_GREEN)\r\33[2K\rFull $(NAME) created  😎\n$(_END)"

$(DIR_OBJ)%.o: $(DIR_SRCS)%.c
	mkdir -p $(DIR_OBJ)
	$(CC) $(CFLAGS) -c $< -o $@
	printf "$(_CYAN)\r\33[2K\rCompling $@$(_END)"

clean:
	rm -rf $(DIR_OBJ)
	echo "$(_RED).o Files Deleted  😱$(_END)"
#	@rm -rf $(OBJECT) $(OBJECT_B)

fclean: clean
	rm -rf $(NAME)
	echo "$(_RED)Library Deleted  😱$(_END)"

re : fclean all

.PHONY: re clean fclean all bonus

.SILENT:

### COLORS ###

_CYAN=$ \033[36m
_GREEN=$ \033[32m
_RED=$ \033[31m
_END=$ \033[0m