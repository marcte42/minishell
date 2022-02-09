

CC			=	gcc
# CFLAGS		=	-g -Wall -Werror -Wextra

NAME		=	minishell

DIR_SRCS	=	./srcs/

DIR_MAIN	=	$(DIR_SRCS)
SRCS_MAIN	=	minishell.c \
				init.c \
				utils.c \
				free.c \

DIR_BUILT	=	$(DIR_SRCS)builtins/
SRCS_BUILT	=	builtin.c \
				builtin_echo.c \
				builtin_cd.c \
				builtin_pwd.c \
				builtin_env.c \
				builtin_unset.c \
				builtin_export.c \
				builtin_exit.c \

DIR_EXEC	=	$(DIR_SRCS)exec/
SRCS_EXEC	=	exec.c \
				exec_utils.c \

DIR_PARSE	=	$(DIR_SRCS)parse/
SRCS_PARSE	=	parse.c \
				parse_pipes.c \
				parse_env.c \
				parse_quotes.c \
				parse_utils.c \
				parse_redirects.c \

DIR_MINILIB	=	./minilib/
SRCS_MINILIB	=	error_funcs.c \
					list_funcs_more.c \
					nlist_funcs.c \
					nlstdel_n_one.c \
					ilist_funcs.c \
					str_funcs.c \
					tab_funcs.c \

DIR_INC		=	./includes/
INCS		=	-I$(DIR_INC)

LIBFT_NAME	=	libft.a
LIBFT		=	$(DIR_LIBFT)$(LIBFT_NAME)

DIR_LIBFT		=	./libft/
DIR_LIBFT_INC	=	$(DIR_LIBFT)
LIBFT_INC		=	libft.h
LIBFT_INCS		=	-I$(DIR_LIBFT)

MINILIB_INCS	=	-I$(DIR_MINILIB)

ALL_INCS	=	$(INCS) $(LIBFT_INCS) $(MINILIB_INCS)
ALL_LIBS	=	-lreadline -L$(DIR_LIBFT) -lft

#TMP for compiling readline lib on mac
# ALL_INCS	=	$(INCS) $(LIBFT_INCS) $(MINILIB_INCS) -I${shell brew --prefix readline}/include
# ALL_LIBS	=	-lreadline -L$(shell brew --prefix readline)/lib -L$(DIR_LIBFT) -lft


DIR_OBJ		=	./objs/

OBJ_MINILIB	=	$(SRCS_MINILIB:.c=.o)

OBJ_MAIN	=	$(SRCS_MAIN:.c=.o)
OBJ_BUILT	=	$(SRCS_BUILT:.c=.o)
OBJ_EXEC	=	$(SRCS_EXEC:.c=.o)
OBJ_PARSE	=	$(SRCS_PARSE:.c=.o)

OBJ_ALL		=	$(OBJ_MAIN) $(OBJ_BUILT) $(OBJ_EXEC) $(OBJ_PARSE) $(OBJ_MINILIB)
OBJS_ALL	=	$(addprefix $(DIR_OBJ),$(OBJ_ALL))


##### RULES ######

all: $(NAME)

$(LIBFT): $(DIR_LIBFT)$(LIBFT_INC) $(SRCS_LIBFT)
	make -C $(DIR_LIBFT)

$(NAME): $(OBJS_ALL) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS_ALL) $(ALL_INCS) $(ALL_LIBS) -o $(NAME)
	printf "$(_GREEN)\r\33[2K\r$(NAME) created  😎\n$(_END)"


$(DIR_OBJ)%.o: $(DIR_MAIN)%.c
	mkdir -p $(DIR_OBJ)
	$(CC) $(CFLAGS) $(ALL_INCS) -c $< -o $@
	printf "$(_CYAN)\r\33[2K\rCompling $@$(_END)"

$(DIR_OBJ)%.o: $(DIR_BUILT)%.c
	mkdir -p $(DIR_OBJ)
	$(CC) $(CFLAGS) $(ALL_INCS) -c $< -o $@
	printf "$(_CYAN)\r\33[2K\rCompling $@$(_END)"

$(DIR_OBJ)%.o: $(DIR_EXEC)%.c
	mkdir -p $(DIR_OBJ)
	$(CC) $(CFLAGS) $(ALL_INCS) -c $< -o $@
	printf "$(_CYAN)\r\33[2K\rCompling $@$(_END)"

$(DIR_OBJ)%.o: $(DIR_PARSE)%.c
	mkdir -p $(DIR_OBJ)
	$(CC) $(CFLAGS) $(ALL_INCS) -c $< -o $@
	printf "$(_CYAN)\r\33[2K\rCompling $@$(_END)"

$(DIR_OBJ)%.o: $(DIR_MINILIB)%.c
	mkdir -p $(DIR_OBJ)
	$(CC) $(CFLAGS) $(ALL_INCS) -c $< -o $@
	printf "$(_CYAN)\r\33[2K\rCompling $@$(_END)"


clean:
	rm -rf $(DIR_OBJ)
	echo "$(_RED).o Files Deleted  😱$(_END)"

fclean: clean
	rm -rf $(NAME)
	make -C $(DIR_LIBFT) fclean
	echo "$(_RED)$(NAME) Deleted  😱$(_END)"

re: fclean all


### Leak testing ####

testf: 

testl:

testv:



.PHONY: all clean fclean re bonus rebonus tests testl testv

.SILENT:

##################
##    COLORS    ##
##################

_GREY=$ \033[30m
_RED=$ \033[31m
_GREEN=$ \033[32m
_YELLOW=$ \033[33m
_BLUE=$ \033[34m
_PURPLE=$ \033[35m
_CYAN=$ \033[36m
_WHITE=$ \033[37m
_END=$ \033[0m


