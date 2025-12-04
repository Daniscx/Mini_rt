
NAME = Mini_rt

CC = cc

CFLAGS = -Wall -g

LIBFT_PATH = libft/

LIBFT_LIB = $(LIBFT_PATH)libft.a


CFILES = \
		main.c\
		parsing.c

OBJECTS = $(CFILES:.c=.o)

all: subsystems $(NAME)

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

subsystems:
	@make -C $(LIBFT_PATH) all
	@make bonus -C $(LIBFT_PATH) all

$(NAME): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) $(LIBFT_LIB) -o $(NAME)

clean:
	make -C $(LIBFT_PATH) clean
	rm -f $(OBJECTS)

fclean: clean
	make -C $(LIBFT_PATH) fclean
	rm -f $(NAME)

re: fclean all



.PHONY: all clean fclean re norm