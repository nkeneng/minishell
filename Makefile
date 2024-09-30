SHELL := /bin/bash
MAKEFLAGS += --warn-undefined-variables
MAKEFILES := libft/Makefile

NAME = project

CC := cc
CFLAGS := -Werror -Wall -Wextra -g
SANITIZE_NAME := $(NAME)_sanitize
LIBFT_DIR := libft
LIBFT_A := $(LIBFT_DIR)/libft.a
LIBFT := -lft
INCLUDES := -L$(LIBFT_DIR)

SRCS_DIR		= ./sources/
OBJS_DIR		= ./objs/

SRCS := main.c #pipex_bonus.c utils.c path.c utils_bonus.c command.c

HEADERS :=

OBJS = $(patsubst $(SRCS_DIR)%.c,$(OBJS_DIR)%.o,$(SRCS))
# TEST_OBJS = $(TESTS_FILES:.c=.o)
#

.PHONY: all, clean, fclean, re, submodules, bonus, libft

all: submodules $(LIBFT_A) $(NAME)

run: all
	./$(NAME)

$(OBJ_DIR):
	@echo "Creating Obj directory.."
	@mkdir -p $(OBJ_DIR)

$(NAME_BONUS): $(OBJS_BONUS) $(LIBFT_A)
	@echo "Linking executable $(NAME_BONUS)..."
	@$(CC) $(CFLAGS) -I$(HEADERS_BONUS) $(OBJS_BONUS) $(INCLUDES) $(LIBFT) -o $@
	@echo "done"

$(NAME): $(OBJS) $(LIBFT_A)
	@echo "Linking executable $(NAME)..."
	$(CC) $(CFLAGS) -I$(HEADERS) $(OBJS) $(INCLUDES) $(LIBFT) -o $@
	@echo "done"

$(OBJ_DIR)/%.o: %.c $(HEADERS) | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

submodules:
	@mkdir -p libft
	@if [ ! -d "$(LIBFT_DIR)" ] || [ -z "$$(ls -A $(LIBFT_DIR))" ]; then \
		echo "Initializing libft and its submodules..."; \
		git submodule add -q -f git@github.com:Moat423/Libft_full.git $(LIBFT_DIR); \
		git submodule update --init --recursive -- $(LIBFT_DIR); \
	else \
		echo "Updating libft and its submodules..."; \
		git submodule update --init --recursive -- $(LIBFT_DIR); \
	fi
	@make -s -C $(LIBFT_DIR) > /dev/null 2>&1

$(LIBFT_A):
	@$(MAKE) -C $(LIBFT_DIR)

clean:
	rm -dRf $(OBJ_DIR)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all


# TEST_SRCS = $(filter-out main.c, $(SRCS))
# TESTS_FILES = $(shell find ./test -name "*_test.c")

# test: $(TEST_SRCS:.c=.o) $(TEST_OBJS)
# 	$(CC) $(CFLAGS) $(TEST_SRCS:.c=.o) $(TEST_OBJS) $(LIBFT) -lcriterion -o test.out && ./test.out
