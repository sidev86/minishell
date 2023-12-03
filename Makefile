NAME = minishell

INC = minishell.h \
	libft/libft.h

SRCS =	minishell.c \
	parser.c \
	executor.c \
	redirection_out.c \
	redirection_in.c \
	env_utils.c \
	lexer.c \
	builtins.c \
	quotes.c \
	var_check.c 

CC = gcc

FLAGS = -g -Wall -Wextra -Werror

OBJS = $(SRCS:.c=.o)

LIBFT = libft/libft.a

$(NAME): $(OBJS) libft
	$(CC) $(FLAGS) $(SRCS) -o $(NAME) -lreadline $(LIBFT)


all: $(NAME) $(OBJS) $(INC)

libft:
	make -C libft

%.o: %.c $(INC)
		$(CC) $(FLAGS) -c $< -o $@
		
clean:
	rm -rf $(OBJS)
	make -C libft clean

fclean: clean
	rm -rf $(NAME) $(OBJS) $(LIBFT)
	
re: fclean all

.PHONY: all libft clean fclean re 

