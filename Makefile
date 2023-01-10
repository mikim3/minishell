NAME = minishell

CC = cc

CFLAGS = -g -Wall -Wextra -Werror

RM = rm
RMFLAGS = -f

INCLUDE = ./include

LIBFT = ./libft

LIBFT_FLAG = -Llibft -lft

READLINE_LIB 	= -lreadline -L${HOME}/.brew/opt/readline/lib
READLINE_INC	= -I${HOME}/.brew/opt/readline/include

SRCDIR = ./src

SRC_BUILTIN_DIR		= $(SRCDIR)/builtin
SRC_DOUBLY_LINKED_LIST_DIR	= $(SRCDIR)/double_linked_list
SRC_ENV_DIR	= $(SRCDIR)/env
SRC_EXECUTE_DIR	= $(SRCDIR)/execute
SRC_MAIN_DIR		= $(SRCDIR)/main
SRC_PARSER_DIR	= $(SRCDIR)/parser
SRC_SIGNAL_DIR	= $(SRCDIR)/signal
SRC_UTILS_DIR	= $(SRCDIR)/utils

SRC_BUILTIN	= ft_cd.c ft_echo.c ft_env.c ft_exit.c ft_export.c ft_pwd.c ft_unset.c 
SRC_BUILTIN	:= $(addprefix $(SRC_BUILTIN_DIR)/, $(SRC_BUILTIN))

SRC_DOUBLY_LINKED_LIST	=	ft_doubly_linked_list_1.c ft_doubly_linked_list_2.c ft_doubly_linked_list_3.c \
							ft_envp_doubly_linked_list.c ft_envp_doubly_linked_list2.c
SRC_DOUBLY_LINKED_LIST	:= $(addprefix $(SRC_DOUBLY_LINKED_LIST_DIR)/, $(SRC_DOUBLY_LINKED_LIST))

SRC_ENV	= env_set.c env_check.c env_pwd_change.c
SRC_ENV	:= $(addprefix $(SRC_ENV_DIR)/, $(SRC_ENV))

SRC_EXECUTE	= execute_cmd.c execute_tree.c execute_redir.c execute_redir2.c execute_file_path.c execute_fork.c execute_fork2.c
SRC_EXECUTE	:= $(addprefix $(SRC_EXECUTE_DIR)/, $(SRC_EXECUTE))

SRC_MAIN	= main.c init.c check_pipeline.c
SRC_MAIN	:= $(addprefix $(SRC_MAIN_DIR)/, $(SRC_MAIN))

SRC_PARSER	=	ft_tokenizer.c ft_token_processing.c ft_tokenizer_util.c ft_syntax_analysis.c ft_syntax_analysis2.c \
				ft_syntax_parse_tree.c ft_syntax_parse_tree2.c ft_parser_util.c ft_parser_util2.c ft_tree.c ft_token_expansion.c \
				ft_token_expansion2.c ft_token_expansion3.c ft_token_expansion_util.c ft_token_here_doc.c ft_token_here_doc2.c
SRC_PARSER 	:= $(addprefix $(SRC_PARSER_DIR)/,$(SRC_PARSER))

SRC_SIGNAL	= signal.c
SRC_SIGNAL 	:= $(addprefix $(SRC_SIGNAL_DIR)/,$(SRC_SIGNAL))

SRC_UTILS	= error.c wrapper_function.c wrapper_function2.c wrapper_function3.c utils.c
SRC_UTILS	:= $(addprefix $(SRC_UTILS_DIR)/, $(SRC_UTILS))

SRCS = $(SRC_BUILTIN) $(SRC_DOUBLY_LINKED_LIST) $(SRC_ENV) $(SRC_EXECUTE) $(SRC_MAIN) $(SRC_PARSER) $(SRC_SIGNAL) $(SRC_UTILS)

OBJS = $(SRCS:.c=.o)

all : $(NAME)

$(NAME): $(OBJS)
	make -C $(LIBFT) bonus
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT_FLAG) -o $(NAME) $(READLINE_LIB)

%.o	: %.c
	$(CC) $(CFLAGS) $(HEADERS) $(READLINE_INC) -Ilibft -c $< -o $@

bonus: 
	make DO_BONUS=1 all
	
clean:
	make -C $(LIBFT) clean
	$(RM) $(RMFLAGS) $(OBJS) $(BONUS_OBJS)

fclean: clean
	$(RM) $(RMFLAGS) $(LIBFT)/libft.a
	$(RM) $(RMFLAGS) $(NAME)

re: 
	make fclean 
	make all

.PHONY: all bonus clean fclean re

