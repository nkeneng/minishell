SHELL := /bin/bash
MAKEFLAGS += --warn-undefined-variables
MAKEFILES := libft/Makefile

NAME = minishell

CC := cc
CFLAGS := -Werror -Wall -Wextra -g
LIBS := -lreadline
SANITIZE_NAME := $(NAME)_sanitize
LIBFT_DIR := libft
LIBFT_A := $(LIBFT_DIR)/libft.a
LIBFT := -lft
INCLUDES := -L$(LIBFT_DIR)

SRCS_DIR		= srcs/
OBJS_DIR		= objs/
TEST_OBJS_DIR	= test_objs/
HEADER_DIR		= includes/

SRCS = $(addprefix $(SRCS_DIR), \
		pipex.c path.c command.c utils.c \
		dummy_helpers/fake_commands.c \
		builtins/ft_cd.c \
		shellprompt.c \
		)

HEADERS := ./includes

OBJS := $(SRCS:$(SRCS_DIR)%.c=$(OBJS_DIR)%.o)

TEST_SRCS = $(filter-out $(SRCS_DIR)main.c $(SRCS_DIR)shellprompt.c, $(SRCS))
TESTS_FILES = $(shell find ./tests -name "*_tests.c")
TEST_OBJS = $(TEST_SRCS:$(SRCS_DIR)%.c=$(TEST_OBJS_DIR)%.o) $(TESTS_FILES:./tests/%.c=$(TEST_OBJS_DIR)%.o)

.PHONY: all clean fclean re submodules libft test

all: submodules $(LIBFT_A) $(NAME)

run: all
	./$(NAME)

$(OBJS_DIR):
	@echo "Creating Obj directory.."
	@mkdir -p $(OBJS_DIR)

$(TEST_OBJS_DIR):
	@echo "Creating Test Obj directory.."
	@mkdir -p $(TEST_OBJS_DIR)

$(NAME): $(OBJS) $(LIBFT_A)
	@echo "Linking executable $(NAME)..."
	$(CC) $(CFLAGS) -I$(HEADERS) $(OBJS) $(INCLUDES) $(LIBFT) $(LIBS) -o $@
	@echo "done"

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c $(HEADERS) | $(OBJS_DIR)
	@$(CC) $(CFLAGS) -I$(HEADERS) -c $< -o $@

$(TEST_OBJS_DIR)%.o: $(SRCS_DIR)%.c $(HEADERS) | $(TEST_OBJS_DIR)
	@$(CC) $(CFLAGS) -I$(HEADERS) -c $< -o $@

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

test: $(LIBFT_A) $(TEST_OBJS)
	@echo "Compiling and running tests..."
	@$(CC) $(CFLAGS) -I$(HEADERS) $(TEST_OBJS) $(INCLUDES) $(LIBFT) $(LIBS) -lcriterion -o test.out
	@./test.out

clean:
	rm -rf $(OBJS_DIR) $(TEST_OBJS_DIR)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME) test.out
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all
