MAKEFLAGS += --no-print-directory

NAME        = miniRT

SRC_DIR     = src
INC_DIR     = includes

SCRSHT_DIR  = screenshots

LIBFT_DIR   = src/aux_libft
LIBFT_A     = $(LIBFT_DIR)/libft.a

MLX_DIR     = linux-minilibx
MLX_A       = $(MLX_DIR)/libmlx.a

OBJ_ROOT        = miniRT_objects
APP_OBJ_DIR     = $(OBJ_ROOT)/miniRT
LIBFT_OBJ_DIR   = $(OBJ_ROOT)/aux_libft

CC			= cc
# CFLAGS		= -Wall -Wextra -Werror -I$(INC_DIR) -I$(LIBFT_DIR) -I$(MLX_DIR)
# CFLAGS_CB   = -Wall -Wextra -Werror -D COLOR_BLEEDING=1 -I$(INC_DIR) -I$(LIBFT_DIR) -I$(MLX_DIR)

# CFLAGS		= -Wall -Wextra -Werror -O3 -I$(INC_DIR) -I$(LIBFT_DIR) -I$(MLX_DIR)
# CFLAGS_CB   = -Wall -Wextra -Werror -D COLOR_BLEEDING=1 -O3 -I$(INC_DIR) -I$(LIBFT_DIR) -I$(MLX_DIR)

CFLAGS   = -Wall -Wextra -Werror -Wno-error=incompatible-pointer-types -O3 -I$(INC_DIR) -I$(LIBFT_DIR)/include -I$(MLX_DIR) -I$(SRC_DIR)/escene/parser
CFLAGS_CB   = -Wall -Wextra -Werror -Wno-error=incompatible-pointer-types -D COLOR_BLEEDING=1 -O3 -I$(INC_DIR) -I$(LIBFT_DIR)/include -I$(MLX_DIR) -I$(SRC_DIR)/escene/parser

LDFLAGS  = -L$(MLX_DIR) -lmlx -L/usr/lib -lXext -lX11 -lm -lz
AR       = ar
ARFLAGS  = rcs

HEADERS = $(wildcard $(INC_DIR)/*.h)

LIBFT_HEADERS = \
	$(LIBFT_DIR)/include/libft.h

# SRCS = \
# 	$(SRC_DIR)/minirt.c \
# 	...

SRCS = $(shell find $(SRC_DIR) -type f -name '*.c' -not -path '$(LIBFT_DIR)/*' -not -path '$(MLX_DIR)/*')
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(APP_OBJ_DIR)/%.o)

# LIBFT_SRCS = \
# 	$(LIBFT_DIR)/src/ft_atof.c \
# 	$(LIBFT_DIR)/src/ft_atoi.c \
# 	$(LIBFT_DIR)/src/ft_atol.c \
# 	$(LIBFT_DIR)/src/ft_bzero.c \
# 	$(LIBFT_DIR)/src/ft_calloc.c \
# 	$(LIBFT_DIR)/src/ft_dbpt_free.c \
# 	$(LIBFT_DIR)/src/ft_isalnum.c \
# 	$(LIBFT_DIR)/src/ft_isalpha.c \
# 	$(LIBFT_DIR)/src/ft_isascii.c \
# 	$(LIBFT_DIR)/src/ft_isdigit.c \
# 	$(LIBFT_DIR)/src/ft_isprint.c \
# 	$(LIBFT_DIR)/src/ft_itoa.c \
# 	$(LIBFT_DIR)/src/ft_lstadd_back.c \
# 	$(LIBFT_DIR)/src/ft_lstadd_front.c \
# 	$(LIBFT_DIR)/src/ft_lstlast.c \
# 	$(LIBFT_DIR)/src/ft_lstnew.c \
# 	$(LIBFT_DIR)/src/ft_lstsize.c \
# 	$(LIBFT_DIR)/src/ft_memchr.c \
# 	$(LIBFT_DIR)/src/ft_memcmp.c \
# 	$(LIBFT_DIR)/src/ft_memcpy.c \
# 	$(LIBFT_DIR)/src/ft_memmove.c \
# 	$(LIBFT_DIR)/src/ft_memset.c \
# 	$(LIBFT_DIR)/src/ft_printf.c \
# 	$(LIBFT_DIR)/src/ft_putchar.c \
# 	$(LIBFT_DIR)/src/ft_putchar_fd.c \
# 	$(LIBFT_DIR)/src/ft_putendl_fd.c \
# 	$(LIBFT_DIR)/src/ft_puthexnum.c \
# 	$(LIBFT_DIR)/src/ft_puthexnumax.c \
# 	$(LIBFT_DIR)/src/ft_putnb.c \
# 	$(LIBFT_DIR)/src/ft_putnbr_fd.c \
# 	$(LIBFT_DIR)/src/ft_putpointer.c \
# 	$(LIBFT_DIR)/src/ft_putstr.c \
# 	$(LIBFT_DIR)/src/ft_putstr_fd.c \
# 	$(LIBFT_DIR)/src/ft_putunmath.c \
# 	$(LIBFT_DIR)/src/ft_selector.c \
# 	$(LIBFT_DIR)/src/ft_split.c \
# 	$(LIBFT_DIR)/src/ft_strchr.c \
# 	$(LIBFT_DIR)/src/ft_strdup.c \
# 	$(LIBFT_DIR)/src/ft_striteri.c \
# 	$(LIBFT_DIR)/src/ft_strjoin.c \
# 	$(LIBFT_DIR)/src/ft_strlcat.c \
# 	$(LIBFT_DIR)/src/ft_strlcpy.c \
# 	$(LIBFT_DIR)/src/ft_strlen.c \
# 	$(LIBFT_DIR)/src/ft_strmapi.c \
# 	$(LIBFT_DIR)/src/ft_strncmp.c \
# 	$(LIBFT_DIR)/src/ft_strnstr.c \
# 	$(LIBFT_DIR)/src/ft_strrchr.c \
# 	$(LIBFT_DIR)/src/ft_strtrim.c \
# 	$(LIBFT_DIR)/src/ft_substr.c \
# 	$(LIBFT_DIR)/src/ft_tolower.c \
# 	$(LIBFT_DIR)/src/ft_toupper.c \
# 	$(LIBFT_DIR)/src/get_next_line.c \
# 	$(LIBFT_DIR)/src/get_next_line_utils.c

LIBFT_SRCS = $(shell find $(LIBFT_DIR) -type f -name '*.c')
LIBFT_OBJS = $(LIBFT_SRCS:$(LIBFT_DIR)/%.c=$(LIBFT_OBJ_DIR)/%.o)

RESET           = \033[0m
TURQUOISE       = \033[0;36m
LIGHT_TURQUOISE = \033[1;36m
DARK_BLUE       = \033[0;34m
LIGHT_GREEN     = \033[1;32m
LIGHT_RED       = \033[1;91m
ORANGE			= \033[38;5;208m
ORANGE_BOLD		= \033[1;38;5;208m

all:
	@if $(MAKE) -q $(NAME) 2>/dev/null; then \
		echo "make: Nothing to be done for 'all'."; \
	else \
		msg=""; \
		if [ ! -f "$(MLX_A)" ]; then \
			msg="minilibx"; \
		fi; \
		if [ ! -f "$(LIBFT_A)" ] || [ -n "$$(find $(LIBFT_DIR) -name '*.c' -newer $(LIBFT_A) 2>/dev/null)" ]; then \
			if [ -n "$$msg" ]; then msg="$$msg, "; fi; \
			msg="$${msg}libft"; \
		fi; \
		needs_minirt=0; \
		if [ ! -f "$(NAME)" ]; then \
			needs_minirt=1; \
		elif [ -n "$$(find $(SRC_DIR) -name '*.c' -not -path '$(LIBFT_DIR)/*' -newer $(NAME) 2>/dev/null)" ]; then \
			needs_minirt=1; \
		elif [ -n "$$(find $(INC_DIR) -name '*.h' -newer $(NAME) 2>/dev/null)" ]; then \
			needs_minirt=1; \
		elif [ ! -f "$(MLX_A)" ] || [ ! -f "$(LIBFT_A)" ]; then \
			needs_minirt=1; \
		fi; \
		if [ $$needs_minirt -eq 1 ]; then \
			if [ -n "$$msg" ]; then msg="$$msg & "; fi; \
			msg="$${msg}miniRT"; \
		fi; \
		if [ -n "$$msg" ]; then \
			echo -e "$(DARK_BLUE)Compiling $$msg...$(RESET)"; \
		fi; \
		$(MAKE) $(NAME); \
	fi

cb:
	@echo -e "$(ORANGE_BOLD)Compiling with COLOR BLEEDING enabled:$(RESET)"
	@$(MAKE) fclean > /dev/null
	@$(MAKE) ENABLE_CB=1 all

$(NAME): $(MLX_A) $(LIBFT_A) $(OBJS)
ifdef ENABLE_CB
	@$(CC) $(CFLAGS_CB) $(OBJS) $(LIBFT_A) $(LDFLAGS) -o $@
else
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT_A) $(LDFLAGS) -o $@
endif
	@echo -e "$(LIGHT_TURQUOISE)miniRT ready!$(RESET)"

$(MLX_A):
	@$(MAKE) -C $(MLX_DIR) > /dev/null 2>&1

$(LIBFT_A): $(LIBFT_OBJS)
	@$(AR) $(ARFLAGS) $@ $^

$(LIBFT_OBJ_DIR)/%.o: $(LIBFT_DIR)/%.c $(LIBFT_HEADERS) | $(LIBFT_OBJ_DIR)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

$(APP_OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS) $(LIBFT_HEADERS) | $(APP_OBJ_DIR)
	@mkdir -p $(dir $@)
ifdef ENABLE_CB
	@$(CC) $(CFLAGS_CB) -c $< -o $@
else
	@$(CC) $(CFLAGS) -c $< -o $@
endif

$(OBJ_ROOT) $(APP_OBJ_DIR) $(LIBFT_OBJ_DIR):
	@mkdir -p $@

clean:
	@echo -e "$(LIGHT_RED)Running an object cleanup...$(RESET)"
	@rm -rf "$(OBJ_ROOT)"
	@$(MAKE) -C $(MLX_DIR) clean > /dev/null 2>&1
	@echo -e "$(TURQUOISE)Cleaning of objects completed!$(RESET)"

fclean:
	@echo -e "$(LIGHT_RED)Running a full cleanup...$(RESET)"
	@rm -rf "$(OBJ_ROOT)"
	@rm -f "$(NAME)" "$(LIBFT_A)"
	@$(MAKE) -C $(MLX_DIR) clean > /dev/null 2>&1
	@echo -e "$(TURQUOISE)Full cleaning finished!$(RESET)"

clean_screenshots:
	@if [ ! -d "./screenshots" ]; then \
		echo -e "$(LIGHT_RED)The directory \"./screenshots/\" does not exist!$(RESET)"; \
	else \
		echo -e "$(LIGHT_RED)Running a screenshots cleanup...$(RESET)"; \
		rm -rf $(SCRSHT_DIR)/*; \
		echo -e "$(LIGHT_GREEN)Screenshots cleanup completed!$(RESET)"; \
	fi

fclean_screenshots:
	@if [ ! -d "./screenshots" ]; then \
		echo -e "$(LIGHT_RED)The directory \"./screenshots/\" does not exist!$(RESET)"; \
	else \
		echo -e "$(LIGHT_RED)Running a screenshots full cleanup...$(RESET)"; \
		rm -rf "$(SCRSHT_DIR)"; \
		echo -e "$(LIGHT_GREEN)Screenshots full cleanup completed!$(RESET)"; \
	fi

re:
	@$(MAKE) fclean
	@echo -e "———"
	@$(MAKE) -s all

test_mandatory:
	@$(MAKE) re
	@$(MAKE) clean
	@echo -e "———"
	@./$(NAME) test_mandatory

test_bonus:
	@$(MAKE) re
	@$(MAKE) clean
	@echo -e "———"
	@./$(NAME) test_bonus

.PHONY: all cb clean fclean re test_mandatory test_bonus

# ----------------------------------------------------------------------------------------------------------------

# "make" works based on whether it is compiled or not, but a make clean can sometimes make it seem like
# there is a relink or no recompilation messages appear, such as from libft. This is for aesthetic reasons,
# as I base it on the ".a" files, and it does not affect the compilation, program operation, or relinks.

# Running  "make cb" causes relink because it attempts to overwrite files, thus generating relink to switch
# between <normal mode> and <color bleeding mode>.

# Remove the "-O3" flag during correction, as it fixes possible errors but greatly improves performance!

# If you see "-e" before the loading messages, etc., when compiling, it's a problem with the terminal;
# try using Bash or their most current versions!

# ----------------------------------------------------------------------------------------------------------------
