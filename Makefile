CC = cc
CFLAGS = -Wall -Werror -Wextra -g
CLIB = -lreadline
READLINE_FLAGS = -I/opt/homebrew/opt/readline/include
READLINE_COMPILE_FLAGS = -L/opt/homebrew/opt/readline/lib

NAME = minishell
SRCS = main.c util.c util2.c \
		$(wildcard built_in/*.c) \
		$(wildcard cmd_exec/*.c) \
		$(wildcard cmd_list/*.c) \
		$(wildcard lexical_analysis/*.c) \
		$(wildcard syntax_analysis/*.c) \
		$(wildcard sig_handle/*.c)
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	@$(MAKE) -C libft all
	$(CC) $(CFLAGS) $(READLINE_COMPILE_FLAGS) $(CLIB) $(OBJS) -o $(NAME) -L ./libft -lft

%.o: %.c
	$(CC) $(CFLAGS) $(READLINE_FLAGS) -c $< -o $@

clean:
	rm -rf $(OBJS)
	@$(MAKE) -C libft clean

fclean: clean
	rm -rf $(NAME)
	@$(MAKE) -C libft fclean

re: fclean all

.PHONY: all re clean fclean
