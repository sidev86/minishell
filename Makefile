NAME = minishell

INC = minishell.h \
	libft/libft.h

SRCS =	minishell.c \
	parser.c \
	executor.c \
	executor_2.c \
	redirection_out.c \
	redirection_out_extra.c \
	redirection_in.c \
	redirection_in_extra.c \
	env_utils.c \
	env_utils_2.c \
	ft_strcmp.c \
	ft_strcpy.c \
	ft_realloc.c \
	ft_strcat.c \
	lexer.c \
	lexer_extra.c \
	builtins.c \
	builtins_2.c \
	builtins_3.c \
	quotes.c \
	var_check.c \
	errors_manager.c \
	signals.c \
	heredoc.c \
	char_checkers.c \
	tokens_counter.c \
	parse_utils.c \
	other_utils.c \
	free_memory.c

CC = gcc

FLAGS = -g -Wall -Wextra -Werror

OBJS = $(SRCS:.c=.o)

LIBFT = libft/libft.a

$(NAME): $(OBJS)
	make -C libft 
	$(CC) $(FLAGS) $(SRCS) -o $(NAME) -lreadline $(LIBFT)


all: $(NAME) $(OBJS) 


%.o: %.c 
		$(CC) $(FLAGS) -c $< -o $@
		
clean:
	rm -rf $(OBJS)
	make -C libft clean

fclean: clean
	rm -rf $(NAME) $(OBJS) $(LIBFT)
	
re: fclean all

.PHONY: all libft clean fclean re 

