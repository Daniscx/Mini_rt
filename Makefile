SHELL = /bin/bash
MAKEFLAGS += --no-print-directory

NAME        = miniRT

INC_DIR     = includes
SRC_DIR     = .
SCRSHT_DIR  = screenshots

LIBFT_DIR   = libft
LIBFT_A     = $(LIBFT_DIR)/libft.a

MLX_DIR     = linux-minilibx
MLX_A       = $(MLX_DIR)/libmlx.a

OBJ_ROOT        = minirtObjects
APP_OBJ_DIR     = $(OBJ_ROOT)/miniRT
LIBFT_OBJ_DIR   = $(OBJ_ROOT)/aux_libft

CC			= cc
# CFLAGS		= -Wall -Wextra -Werror -I$(INC_DIR) -I$(LIBFT_DIR) -I$(MLX_DIR)
# CFLAGS_CB   = -Wall -Wextra -Werror -D COLOR_BLEEDING=1 -I$(INC_DIR) -I$(LIBFT_DIR) -I$(MLX_DIR)

# CFLAGS		= -Wall -Wextra -Werror -I$(INC_DIR) -I$(LIBFT_DIR) -O3 -I$(MLX_DIR)
# CFLAGS_CB   = -Wall -Wextra -Werror -D COLOR_BLEEDING=1 -I$(INC_DIR) -O3 -I$(LIBFT_DIR) -I$(MLX_DIR)

CFLAGS   = -Wall -Wextra -Werror   -g -I$(INC_DIR) -I$(LIBFT_DIR) -I$(MLX_DIR)
CFLAGS_CB   = -Wall -Wextra -Werror  -D COLOR_BLEEDING=1 -O3 -I$(INC_DIR) -I$(LIBFT_DIR) -I$(MLX_DIR)

LDFLAGS  = -L$(MLX_DIR) -lmlx -L/usr/lib -lXext -lX11 -lm -lz
AR       = ar
ARFLAGS  = rcs

SRCS =		vector/Vector.c \
			vector/vector_utils.c \
			texture/texture_effects.c \
			texture/texture.c \
			render/screenshot.c \
			render/render.c \
			render/render_high.c \
			ray/ray.c \
			objects/shpere.c \
			objects/plane.c \
			objects/cylinder.c \
			objects/objects.c \
			objects/cone.c \
			light/ligh_utlis.c \
			light/light.c \
			escene/escene.c \
			hit/hit.c \
			escene/parser/parser_validators.c \
			escene/parser/parser_elements.c \
			escene/parser/parser_file.c \
			escene/parser/parser_assignment.c \
			escene/parser/parser_destructors.c \
			escene/parser/parsin_debug.c \
			camera/init.c \
			camera/init_window.c \
			camera/events_utils.c \
			camera/events_select.c \
			camera/events_print.c \
			camera/events_loop.c \
			camera/events_mouse.c \
			camera/events_key.c \
			camera/events_drag.c \
			camera/collisions.c \
			camera/camera.c \
			ambient_light/ambient_light.c \
			main.c 
OBJS = $(SRCS:%.c=$(APP_OBJ_DIR)/%.o)
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
ifdef ENABLE_CB
	@$(CC) $(CFLAGS_CB) -c $< -o $@
else
	@$(CC) $(CFLAGS) -c $< -o $@
endif
	$(call show_progress)

$(OBJ_ROOT) $(APP_OBJ_DIR) $(LIBFT_OBJ_DIR):
	@mkdir -p $@

clean:
	@echo -e "$(LIGHT_RED)Running a objects cleanup...$(RESET)"
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

# The makefile works fine, both for miniRT and libft, but there is a visual bug with already compiled
# code when files are modified or deleted from libft. Despite this, the makefile works perfectly,
# avoiding relinks, etc. It is just a visual loading error!
# Try running make in miniRT, make fclean in libft, and make again in miniRT. You'll see the bug when loading!

# Running  "make" cb causes relink because it attempts to overwrite files, thus generating relink to switch
# between <normal mode> and <color bleeding mode>.

# Remove the "-O3" flag during correction, as it fixes possible errors but greatly improves performance!

# If you see "-e" before the loading messages, etc., when compiling, it's a problem with the terminal; try using Bash!