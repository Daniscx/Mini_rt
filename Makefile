
SHELL = /bin/bash
MAKEFLAGS += --no-print-directory

NAME        = miniRT

SRC_DIR     = src
INC_DIR     = include

LIBFT_DIR   = src/aux_libft
LIBFT_A     = $(LIBFT_DIR)/libft.a

MLX_DIR     = linux-minilibx
MLX_A       = $(MLX_DIR)/libmlx.a

OBJ_ROOT        = minirtObjects
APP_OBJ_DIR     = $(OBJ_ROOT)/miniRT
LIBFT_OBJ_DIR   = $(OBJ_ROOT)/aux_libft

CC       = cc
# CFLAGS   = -Wall -Wextra -Werror -I$(INC_DIR) -I$(LIBFT_DIR) -I$(MLX_DIR)

CFLAGS   = -Wall -Wextra -Werror -Wno-error=incompatible-pointer-types -I$(INC_DIR) -I$(LIBFT_DIR) -I$(MLX_DIR)

LDFLAGS  = -L$(MLX_DIR) -lmlx -L/usr/lib -lXext -lX11 -lm -lz
AR       = ar
ARFLAGS  = rcs

SRCS = $(shell find $(SRC_DIR) -type f -name '*.c' -not -path '$(LIBFT_DIR)/*' -not -path '$(MLX_DIR)/*')
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(APP_OBJ_DIR)/%.o)

LIBFT_SRCS = $(shell find $(LIBFT_DIR) -type f -name '*.c')
LIBFT_OBJS = $(LIBFT_SRCS:$(LIBFT_DIR)/%.c=$(LIBFT_OBJ_DIR)/%.o)

RESET           = \033[0m
TURQUOISE       = \033[0;36m
LIGHT_TURQUOISE = \033[1;36m
DARK_BLUE       = \033[0;34m
LIGHT_GREEN     = \033[1;32m
LIGHT_RED       = \033[1;91m

TOTAL_STEPS = $(words $(SRCS) $(LIBFT_SRCS))
COMPILED = 0

define show_progress
	$(eval COMPILED := $(shell echo $$(($(COMPILED) + 1))))
	@total=$(TOTAL_STEPS); \
	curr=$(COMPILED); \
	width=60; \
	hashes=$$(( curr * width / total )); \
	[ "$$hashes" -ge 0 ] || hashes=0; \
	dots=$$(( width - hashes )); \
	[ "$$dots" -ge 0 ] || dots=0; \
	green=$$(printf "\033[1;32m"); \
	reset=$$(printf "\033[0m"); \
	printf "\rCompiling miniRT: ["; \
	bar=$$(printf "%*s" "$$hashes" ""); bar=$${bar// /#}; \
	printf "%s" "$$green$$bar$$reset"; \
	dot=$$(printf "%*s" "$$dots" ""); dot=$${dot// /.}; \
	printf "%s" "$$dot"; \
	printf "] %d/%d" "$$curr" "$$total"; \
	if [ "$$curr" -ge "$$total" ]; then printf " ✓\n"; fi;
endef

all: $(NAME)

$(NAME): $(MLX_A) $(LIBFT_A) $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT_A) $(LDFLAGS) -o $@
	@if [ $(COMPILED) -gt 0 ]; then \
		echo -e "$(LIGHT_TURQUOISE)miniRT ready!$(RESET)"; \
	fi

$(MLX_A):
	@echo -e "$(DARK_BLUE)Compiling minilibx...$(RESET)"
	@$(MAKE) -C $(MLX_DIR) > /dev/null 2>&1

$(LIBFT_A): $(LIBFT_OBJS)
	@$(AR) $(ARFLAGS) $@ $^

$(LIBFT_OBJ_DIR)/%.o: $(LIBFT_DIR)/%.c | $(LIBFT_OBJ_DIR)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@
	$(call show_progress)

$(APP_OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(APP_OBJ_DIR)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@
	$(call show_progress)

$(OBJ_ROOT) $(APP_OBJ_DIR) $(LIBFT_OBJ_DIR):
	@mkdir -p $@

clean:
	@echo -e "$(LIGHT_RED)Running object cleanup...$(RESET)"
	@rm -rf "$(OBJ_ROOT)"
	@$(MAKE) -C $(MLX_DIR) clean > /dev/null 2>&1
	@echo -e "$(TURQUOISE)Cleaning of objects completed!$(RESET)"

fclean:
	@echo -e "$(LIGHT_RED)Running a full cleanup...$(RESET)"
	@rm -rf "$(OBJ_ROOT)"
	@rm -f "$(NAME)" "$(LIBFT_A)"
	@$(MAKE) -C $(MLX_DIR) clean > /dev/null 2>&1
	@echo -e "$(TURQUOISE)Full cleaning finished!$(RESET)"

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

.PHONY: all clean fclean re test_mandatory test_bonus

# The makefile works fine, both for miniRT and libft, but there is a visual bug with already compiled
# code when files are modified or deleted from libft. Despite this, the makefile works perfectly,
# avoiding relinks, etc. It is just a visual loading error! 
# Try running make in miniRT, make fclean in libft, and make again in miniRT. You'll see the bug when loading!

# If you see "-e" before the loading messages, etc., when compiling, it's a problem with the terminal; try using Bash!
