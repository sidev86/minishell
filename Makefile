NAME = minishell

INC = minishell.h

SRCS =	minishell.c \
	parser.c \
	executor.c \
	redirection_out.c \
	redirection_in.c \
	ft_split.c \
	env_utils.c \
	lexer.c \
	ft_substr.c \
	ft_strjoin.c \
	ft_putstr_fd.c \
	ft_itoa.c \
	builtins.c \
	ft_strchr.c \
	quotes.c \
	var_check.c 

CC = gcc

FLAGS = -g -Wall -Wextra -Werror

OBJS = $(SRC:.c=.o)

$(NAME): $(OBJS)
	$(CC) $(FLAGS) $(SRCS) -o $(NAME) -lreadline


all: $(NAME) $(OBJS) $(INC)

%.o: %.c $(INC)
		$(CC) $(FLAGS) -c $< -o $@
		
clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME) $(OBJS)
	
re: fclean all

.PHONY: all clean fclean re 

