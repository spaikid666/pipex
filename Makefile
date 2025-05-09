NAME = pipex

SRCS = pipex.c \
	pipex_utils_1.c \
	pipex_utils_2.c \
	ft_split.c

OBJS = $(SRCS:.c=.o)

CFLAGS = -Wall -Werror -Wextra

CC = cc

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re