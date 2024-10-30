SHELL := /bin/bash
#MAKEFLAGS += --warn-undefined-variables
MAKEFILES := libft/Makefile

NAME = minishell

CC := cc
CFLAGS := -Werror -Wall -Wextra -g
LIBS := -lreadline
LIBFT_DIR := libft
LIBFT_A := $(LIBFT_DIR)/libft.a
LIBFT := -lft
INCLUDES := -L$(LIBFT_DIR)

SRCS_DIR		= srcs/
OBJS_DIR		= objs/
TEST_OBJS_DIR	= test_objs/
HEADER_DIR		= includes/

DIRS = $(addprefix $(OBJS_DIR), . builtins dummy_helpers pipex lst reading parser tests)

#		$(addprefix dummy_helpers/, fake_commands.c)
SRCS = $(addprefix $(SRCS_DIR), \
		$(addprefix pipex/, pipex.c path.c command.c utils.c) \
		$(addprefix lst/ft_, lstcreate_addback.c free_command.c printf_list.c) \
		$(addprefix reading/, here_doc.c rl_gets.c) \
		$(addprefix builtins/ft_, cd.c echo.c pwd.c unset.c env.c exit.c export.c) \
		init_envp.c main.c \
		)

HEADERS := ./includes

OBJS := $(SRCS:$(SRCS_DIR)%.c=$(OBJS_DIR)%.o)

TEST_SRCS = $(filter-out $(SRCS_DIR)main.c $(SRCS_DIR)shellprompt.c, $(SRCS))
TESTS_FILES = $(shell find ./tests -name "*_tests.c")
TEST_OBJS = $(TEST_SRCS:$(SRCS_DIR)%.c=$(TEST_OBJS_DIR)%.o) $(TESTS_FILES:./tests/%.c=$(TEST_OBJS_DIR)%.o)

.PHONY: all clean fclean re submodules libft test parse

all: submodules $(LIBFT_A) $(NAME)

build: $(OBJS) $(LIBFT_A)
	@echo "Compiling $(MAIN)..."
	@$(CC) $(CFLAGS) -I$(HEADERS) -c $(MAIN) -o $(OBJS_DIR)$(notdir $(MAIN:.c=.o))
	@echo "Linking executable $(NAME)..."
	$(CC) $(CFLAGS) -I$(HEADERS) $(OBJS) $(OBJS_DIR)$(notdir $(MAIN:.c=.o)) $(INCLUDES) $(LIBFT) $(LIBS) -o $(NAME)
	@echo "done"

#hello world

run: all
	./$(NAME)

# parse: NAME = parse_minishell
# parse: MAIN = srcs/tests/test_word_list.c
# parse: build

exec: NAME = exec_minishell
exec: MAIN = srcs/main.c
exec: build

$(DIRS):
	mkdir -p $@

$(TEST_OBJS_DIR):
	@echo "Creating Test Obj directory.."
	@mkdir -p $(TEST_OBJS_DIR)

$(NAME): $(OBJS) $(LIBFT_A) $(MAIN:.c=.o)
	@echo "Linking executable $(NAME)..."
	$(CC) $(CFLAGS) -I$(HEADERS) $(OBJS) $(MAIN_OBJ) $(INCLUDES) $(LIBFT) $(LIBS) -o $@
	@echo "done"

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c $(HEADERS) | $(DIRS)
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

debug: all
	lldb $(NAME)

clean:
	rm -rf $(OBJS_DIR) $(TEST_OBJS_DIR) $(MAIN:.c=.o)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME) test.out
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all
