SRCS = 0_main.c 1_arg_file_check.c 2_child.c \
       3_ft_execute.c 9_error.c 9_utils.c gnl.c \
       ft_split.c gnl_utils.c

NAME = pipex
CC = cc
CFLAGS = -Wall -Wextra -Werror
OBJC = $(SRCS:.c=.o)
RM = rm -f

all: $(NAME)

$(NAME): $(OBJC)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJC)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJC) $(OBJCB)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
