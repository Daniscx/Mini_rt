
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

CFLAGS   = -Wall -Wextra -Werror -Wno-error=incompatible-pointer-types -I$(INC_DIR) -I$(LIBFT_DIR) -I$(MLX_DIR) # Cluster 🡹

LDFLAGS  = -L$(MLX_DIR) -lmlx -L/usr/lib -lXext -lX11 -lm -lz
AR       = ar
ARFLAGS  = rcs

SRCS = $(shell find $(SRC_DIR) -type f -name '*.c' -not -path '$(LIBFT_DIR)/*' -not -path '$(MLX_DIR)/*')
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(APP_OBJ_DIR)/%.o)

LIBFT_SRCS = $(shell find $(LIBFT_DIR) -type f -name '*.c')
LIBFT_OBJS = $(LIBFT_SRCS:$(LIBFT_DIR)/%.c=$(LIBFT_OBJ_DIR)/%.o)

RESET           = \001\033[0m\002
TURQUOISE       = \001\033[0;36m\002
LIGHT_TURQUOISE = \001\033[1;36m\002
LIGHT_GREEN     = \001\033[1;32m\002
LIGHT_RED       = \001\033[1;91m\002

TOTAL_STEPS = $(words $(SRCS) $(LIBFT_SRCS))

define show_progress
	@total=$(TOTAL_STEPS); \
	[ "$$total" -gt 0 ] || total=1; \
	curr=$$(find "$(OBJ_ROOT)" -type f -name "*.o" 2>/dev/null | wc -l); \
	width=60; \
	hashes=$$(( curr * width / total )); \
	[ "$$hashes" -ge 0 ] || hashes=0; \
	dots=$$(( width - hashes )); \
	[ "$$dots" -ge 0 ] || dots=0; \
	green=$$(printf "\033[1;32m"); \
	reset=$$(printf "\033[0m"); \
	printf "\rCompiling: ["; \
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
	@echo -e "$(LIGHT_TURQUOISE)miniRT ready!$(RESET)"

$(MLX_A):
	@$(MAKE) -C $(MLX_DIR)

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
	@$(MAKE) -C $(MLX_DIR) clean
	@echo -e "$(TURQUOISE)Cleaning of objects completed!$(RESET)"

fclean:
	@echo -e "$(LIGHT_RED)Running a full cleanup...$(RESET)"
	@rm -rf "$(OBJ_ROOT)"
	@rm -f "$(NAME)" "$(LIBFT_A)"
	@$(MAKE) -C $(MLX_DIR) clean
	@echo -e "$(TURQUOISE)Full cleaning finished!$(RESET)"

re:
	@$(MAKE) fclean
	@$(MAKE) -s all

.PHONY: all clean fclean re
