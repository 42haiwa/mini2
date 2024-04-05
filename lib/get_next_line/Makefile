NAME      := libgnl.a
CFLAGS     := -Wall -Wextra -Werror

SRC      := get_next_line.c \
		get_next_line_utils.c

OBJ      := $(SRC:.c=.o)
ARFLAGS   := rcs
RM		    := rm -f

%.o:		%.c
			$(CC) $(CFLAGS) -c $< -o $@

$(NAME):	$(OBJ) all
			$(AR) $(ARFLAGS) $(NAME) $(OBJ)

all:		$(NAME)

clean:
			$(RM) *.o */*.o */*/*.o

fclean:		clean
			$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re 

