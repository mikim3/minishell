NAME = libft.a
CC = gcc
CFLAGS = -Wall -Wextra -Werror
RM = rm
RMFLAGS = -f
AR = ar
ARFLAGS = -rcs
SRCS = ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c ft_issign.c ft_isspace.c ft_itoa.c ft_itoa_base.c ft_uitoa_base.c ft_uintptr_to_a.c ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c ft_strchr.c ft_strrchr.c ft_strdup.c ft_strndup.c ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strcmp.c ft_strncmp.c ft_toupper.c ft_tolower.c ft_strnstr.c ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_printf_bonus.c ft_printf_flags_bonus.c ft_printf_output_length_bonus.c ft_printf_set_data.c ft_printf_set_output.c ft_printf_structs_bonus.c ft_printf_utils_bonus.c

BONUS_SRCS = ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c

OBJS = $(SRCS:.c=.o)

BONUS_OBJS = $(BONUS_SRCS:.c=.o)

ifdef DO_BONUS
	OBJECTS = $(OBJS) $(BONUS_OBJS)
else
	OBJECTS = $(OBJS)
endif

all : $(NAME)

$(NAME): $(OBJECTS)
	$(AR) $(ARFLAGS) $(NAME) $(OBJECTS)

bonus: 
	make DO_BONUS=1 all

clean:
	$(RM) $(RMFLAGS) $(OBJS) $(BONUS_OBJS)

fclean: clean
	$(RM) $(RMFLAGS) $(NAME)

re: fclean all

.PHONY:all bonus clean fclean re
