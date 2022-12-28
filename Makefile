NAME = minishell

CC = cc
# CFLAGS = -Wall -Wextra -Werror -g
CFLAGS =  -g
RM = rm
RMFLAGS = -f

INCLUDE = ./include

LIBFT = ./libft

LIBFT_FLAG = -Llibft -lft

READLINE_FLAG = -lreadline

SRCDIR = ./src

SRC_BUILTIN_DIR		= $(SRCDIR)/builtin
SRC_DOUBLY_LINKED_LIST_DIR	= $(SRCDIR)/double_linked_list
SRC_ENV_DIR	= $(SRCDIR)/env
SRC_EXECUTE_DIR	= $(SRCDIR)/execute
SRC_MAIN_DIR		= $(SRCDIR)/main
SRC_PARSER_DIR	= $(SRCDIR)/parser

SRC_BUILTIN	= 
SRC_BUILTIN	:= $(addprefix $(SRC_BUILTIN_DIR)/, $(SRC_BUILTIN))

SRC_DOUBLY_LINKED_LIST	= ft_doubly_linked_list_1.c ft_doubly_linked_list_2.c ft_doubly_linked_list_3.c ft_envp_doubly_linked_list.c
SRC_DOUBLY_LINKED_LIST	:= $(addprefix $(SRC_DOUBLY_LINKED_LIST_DIR)/, $(SRC_DOUBLY_LINKED_LIST))

SRC_ENV	= env_set.c
SRC_ENV	:= $(addprefix $(SRC_ENV_DIR)/, $(SRC_ENV))

SRC_EXECUTE	= execute_cmd.c execute_tree.c
SRC_EXECUTE	:= $(addprefix $(SRC_EXECUTE_DIR)/, $(SRC_EXECUTE))

SRC_MAIN	= main.c
SRC_MAIN	:= $(addprefix $(SRC_MAIN_DIR)/, $(SRC_MAIN))

SRC_PARSER	= ft_tokenizer.c ft_token_processing.c ft_tokenizer_util.c ft_syntax_analysis.c ft_syntax_parse_tree.c ft_syntax_util.c ft_tree.c ft_token_expansion.c
SRC_PARSER 	:= $(addprefix $(SRC_PARSER_DIR)/,$(SRC_PARSER))

SRCS = $(SRC_BUILTIN) $(SRC_DOUBLY_LINKED_LIST) $(SRC_ENV) $(SRC_EXECUTE) $(SRC_MAIN) $(SRC_PARSER)  

OBJS = $(SRCS:.c=.o)

all : $(NAME)

$(NAME): $(OBJS)
	make -C $(LIBFT) bonus
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT_FLAG) $(READLINE_FLAG) -o $(NAME)

%.o	: %.c
	$(CC) $(CFLAGS) $(HEADERS) -Ilibft -c $< -o $@

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

