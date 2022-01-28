

CC			=	gcc
CFLAGS		=	-Wall -Werror -Wextra

NAME		=	minishell

DIR_SRCS	=	./srcs/

DIR_MAIN	=	$(DIR_SRCS)
SRCS_MAIN	=	minishell.c \
				init.c \
				utils.c \
				free.c \

DIR_BUILT	=	$(DIR_SRCS)builtins/
SRCS_BUILT	=	builtin_cd.c \
				builtin_echo.c \
				builtin_env.c \
				builtin_exit.c \
				builtin_export.c \
				builtin_pwd.c \
				builtin_unset.c \

DIR_EXEC	=	$(DIR_SRCS)executor/
SRCS_EXEC	=	exec.c \
				utils_exec.c \

DIR_PARSE	=	$(DIR_SRCS)parser/
SRCS_PARSE	=	parse.c \
				env.c \
				quotes.c \
				utils_parse.c \

# may move these to be in the SRCS folder, if the cors are gonna get all annoying about it...
DIR_MINILIB	=	./minilib/
SRCS_MINILIB	=	big_str_funcs.c \
					error_funcs.c \
					nlist_funcs.c \
					nlstdel_n_one.c \
					ilist_funcs.c \
					put_funcs.c \
					str_funcs.c \
					tab_funcs.c \

#SRCS_MINILIB	=	atoi_funcs.c \
					big_str_funcs.c \
					error_funcs.c \
					ft_split.c \
					ft_strjoin.c \
					is_funcs.c \
					list_funcs.c \
					list_funcs_more.c \
					nlist_funcs.c \
					nlstdel_n_one.c \
					ilist_funcs.c \
					put_funcs.c \
					str_funcs.c \
					tab_funcs.c \
					gnl.c \
					gnl_utils.c \


DIR_INC		=	./includes/
#DIR_INC		=	./
INCS		=	-I$(DIR_INC)

LIBFT_NAME	=	libft.a
DIR_LIBFT	=	./libft/
LIBFT		=	$(DIR_LIBFT)$(LIBFT_NAME)

DIR_LIBFT_INC	=	$(DIR_LIBFT)
LIBFT_INC		=	libft.h
LIBFT_INCS		=	$(addprefix -I,$(addprefix $(DIR_LIBFT_INC), $(LIBFT_INC)))




# if we had a library we would add its .h here
#ALL_INCS	=	$(INCS) -I$(DIR_MINILIB)
ALL_INCS	=	$(INCS)	$(LIBFT_INCS)

DIR_OBJ		=	./objs/

#OBJ_MINILIB	=	$(SRCS_MINILIB:.c=.o)
#OBJ_SHELL	=	$(SRCS_SHELL:.c=.o) $(OBJ_MINILIB)

OBJ_MAIN	=	$(SRCS_MAIN:.c=.o)
OBJ_BUILT	=	$(SRCS_BUILT:.c=.o)
OBJ_EXEC	=	$(SRCS_EXEC:.c=.o)
OBJ_PARSE	=	$(SRCS_PARSE:.c=.o)

OBJ_ALL		=	$(OBJ_MAIN) $(OBJ_BUILT) $(OBJ_EXEC) $(OBJ_PARSE) 
OBJS_ALL	=	$(addprefix $(DIR_OBJ),$(OBJ_ALL))


##### RULES ######

all: $(NAME)

#$(LIBFT): $(LIBFT_INC) 

$(NAME): $(OBJS_ALL)
	$(CC) $(CFLAGS) $(ALL_INCS) $(OBJS_ALL) -o $(NAME)
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


