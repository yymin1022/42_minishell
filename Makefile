CC = cc
CFLAGS = -Wall -Werror -Wextra -g
CLIB = -lreadline

NAME = minishell
SRCS = main.c util.c \
		$(wildcard lexical_analysis/*.c) \
		$(wildcard syntax_analysis/*.c) \
		$(wildcard cmd_list/*.c) \
		$(wildcard built_in/*.c)
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	@$(MAKE) -C libft all
	$(CC) $(CFLAGS) $(CLIB) $(OBJS) -o $(NAME) -L ./libft -lft

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJS)
	@$(MAKE) -C libft clean

fclean: clean
	rm -rf $(NAME)
	@$(MAKE) -C libft fclean

re: fclean all

.PHONY: all re clean fclean
