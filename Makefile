NAME := minishell

CFLAGS := -g -Iinclude -Werror -Wall -Wextra
LDFLAGS := -Llib/libft -lft -Llib/get_next_line -lgnl -lreadline

SRC := src/main.c \
		src/lexing/lexing.c \
		src/lexing/pre_lexing.c \
		src/lexing/lexing_utils.c \
		src/builtins/exit.c \
		src/builtins/cd.c \
		src/builtins/builtins.c \
		src/builtins/pwd.c \
		src/builtins/env.c \
		src/builtins/echo.c \
		src/builtins/export.c \
		src/builtins/export_utils.c \
		src/ft_close.c \
		src/extra.c \
		src/node_init.c \
		src/node_add_son.c \
		src/node_print_recurse.c \
		src/parse_envp.c \
		src/execution/pre_execution.c \
		src/execution/execution.c \
		src/execution/execution2.c \
		src/execution/execution3.c \
		src/execution/execution_utils.c \
		src/handler.c \
		src/get_path.c \
		src/parse_io.c \
		src/parse_io2.c \
		src/get_d_quote.c \
		src/get_quote.c \
		src/replace_env.c \
		src/builtins/unset.c \
		src/utils/utils.c \
		src/utils/utils2.c \
		src/utils/utils3.c \
		src/utils/utils4.c \
		src/utils/utils5.c \
		src/builtins/export_unset_utils.c \
		src/parsing/bill_three.c \
		src/parsing/parse_io_n.c \
		src/parsing/parsing_utils.c \
		src/parsing/heredoc.c
OBJ := $(SRC:.c=.o)

%.o:		%.c
			$(CC) $(CFLAGS) -c $< -o $@

$(NAME):	lft_all gnl_all $(OBJ)
			$(CC) $(OBJ) -o $(NAME) $(LDFLAGS)

gnl_all:
			$(MAKE) -C lib/get_next_line
gnl_clean:
			$(MAKE) clean -C lib/get_next_line
gnl_fclean:
			$(MAKE) fclean -C lib/get_next_line
gnl_re:
			$(MAKE) re -C lib/get_next_line

lft_all:
			$(MAKE) -C lib/libft
lft_clean:
			$(MAKE) clean -C lib/libft
lft_fclean:
			$(MAKE) fclean -C lib/libft
lft_re:
			$(MAKE) re -C lib/libft

all:		$(NAME)

clean:		lft_clean gnl_clean
			$(RM) -f $(OBJ)

fclean:		lft_fclean gnl_fclean clean
			$(RM) -f $(NAME)

re:			gnl_re fclean all

.PHONY:		all clean fclean re gnl_all gnl_clean gnl_fclean gnl_re lft_all lft_clean lft_fclean lft_re

