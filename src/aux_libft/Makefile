MAKEFLAGS += --no-print-directory

NAME = libft.a

CC = cc
CFLAGS = -Wall -Wextra -Werror -I$(INC_DIR)
AR = ar
ARFLAGS = rcs

SRC_DIR = src
INC_DIR = include
OBJ_DIR = ../../miniRT_objects/aux_libft

RESET = \033[0m
GREEN = \033[1;32m
CYAN = \033[1;36m
COMPILE = \033[1;33m
RED = \033[1;91m

SRCS = $(SRC_DIR)/ft_isalpha.c \
	   $(SRC_DIR)/ft_isdigit.c \
	   $(SRC_DIR)/ft_isalnum.c \
	   $(SRC_DIR)/ft_isascii.c \
	   $(SRC_DIR)/ft_isprint.c \
	   $(SRC_DIR)/ft_strlen.c \
	   $(SRC_DIR)/ft_memset.c \
	   $(SRC_DIR)/ft_bzero.c \
	   $(SRC_DIR)/ft_memcpy.c \
	   $(SRC_DIR)/ft_memmove.c \
	   $(SRC_DIR)/ft_strlcpy.c \
	   $(SRC_DIR)/ft_strlcat.c \
	   $(SRC_DIR)/ft_toupper.c \
	   $(SRC_DIR)/ft_tolower.c \
	   $(SRC_DIR)/ft_strchr.c \
	   $(SRC_DIR)/ft_strrchr.c \
	   $(SRC_DIR)/ft_strncmp.c \
	   $(SRC_DIR)/ft_memchr.c \
	   $(SRC_DIR)/ft_memcmp.c \
	   $(SRC_DIR)/ft_strnstr.c \
	   $(SRC_DIR)/ft_atoi.c \
	   $(SRC_DIR)/ft_strdup.c \
	   $(SRC_DIR)/ft_calloc.c \
	   $(SRC_DIR)/ft_substr.c \
	   $(SRC_DIR)/ft_strjoin.c \
	   $(SRC_DIR)/ft_strtrim.c \
	   $(SRC_DIR)/ft_split.c \
	   $(SRC_DIR)/ft_itoa.c \
	   $(SRC_DIR)/ft_strmapi.c \
	   $(SRC_DIR)/ft_striteri.c \
	   $(SRC_DIR)/ft_putchar_fd.c \
	   $(SRC_DIR)/ft_putstr_fd.c \
	   $(SRC_DIR)/ft_putendl_fd.c \
	   $(SRC_DIR)/ft_putnbr_fd.c \
	   $(SRC_DIR)/ft_putunmath.c \
	   $(SRC_DIR)/ft_putstr.c \
	   $(SRC_DIR)/get_next_line.c \
	   $(SRC_DIR)/get_next_line_utils.c \
	   $(SRC_DIR)/ft_putpointer.c \
	   $(SRC_DIR)/ft_putnb.c \
	   $(SRC_DIR)/ft_selector.c \
	   $(SRC_DIR)/ft_putchar.c \
	   $(SRC_DIR)/ft_puthexnumax.c \
	   $(SRC_DIR)/ft_puthexnum.c \
	   $(SRC_DIR)/ft_printf.c \
	   $(SRC_DIR)/ft_atol.c \
	   $(SRC_DIR)/ft_dbpt_free.c \
	   $(SRC_DIR)/ft_atof.c \
	   $(SRC_DIR)/ft_lstnew.c \
	   $(SRC_DIR)/ft_lstadd_front.c \
	   $(SRC_DIR)/ft_lstsize.c \
	   $(SRC_DIR)/ft_lstlast.c \
	   $(SRC_DIR)/ft_lstadd_back.c

OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

$(NAME): $(OBJS)
	@echo -e "$(COMPILE)Compilando libft.a$(RESET)"
	@$(AR) $(ARFLAGS) $@ $^
	@echo -e "$(GREEN)libft.a ready!$(RESET)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $@

clean:
	@if [ ! -d "../../miniRT_objects/miniRT" ]; then \
		rm -rf "../../miniRT_objects"; \
	else \
		rm -rf $(OBJ_DIR); \
	fi

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

# If you see "-e" before the loading messages, etc., when compiling, it's a problem with the terminal;
# try using Bash or their most current versions!
