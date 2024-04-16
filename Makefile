SRC			= src/main.c \
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
		src/execution/execution4.c \
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
		src/gnl/get_next_line.c \
		src/gnl/get_next_line_utils.c \
		src/parsing/heredoc.c

OBJ 		= $(SRC:.c=.o)

FT			= lib/libft
LIBFT 		= lib/libft/libft.a
GNL			= lib/gnl
LIBGNL		= lib/gnl/libgnl.a

CC 			= cc
CLONE		= git clone --depth=1
CFLAGS 		= -Wall -Wextra -Werror -Iinclude -g
LDFLAGS 	= -lreadline

NAME 		= minishell

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT) #$(LIBGNL)
	$(CC) $(CFLAGS) $^ -o $(NAME) $(LDFLAGS)

$(LIBFT):
	$(MAKE) -C lib/libft
	
# $(LIBGNL):
# 	$(MAKE) -C lib/gnl

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

debug: fclean
	$(MAKE) DEBUG=1 all

clean: 
	if [ -d "$(FT)" ]; then $(MAKE) clean -C $(FT); fi
	$(RM) $(OBJ)
#	if [ -d "$(GNL)" ]; then $(MAKE) clean -C $(GNL); fi

fclean: clean
	$(RM) $(LIBFT)
	$(RM) $(NAME)

clear:
	$(RM) -r $(FT)
	$(RM) -r $(GNL)

re: fclean all

-include myrules.mk

.PHONY: all debug clean fclean clear re

