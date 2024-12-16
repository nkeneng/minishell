SHELL := /bin/bash
#MAKEFLAGS += --warn-undefined-variables
MAKEFILES := libft/Makefile

NAME = minishell

CC := cc
#-fPIE: Used during compilation to generate position-independent code
CFLAGS := -Werror -Wall -Wextra -Wextra -g -fPIE
LIBS := -lreadline
LIBFT_DIR := libft
LIBFT_A := $(LIBFT_DIR)/libft.a
LIBFT := -lft
INCLUDES := -L$(LIBFT_DIR)

SRCS_DIR		= srcs/
OBJS_DIR		= objs/
TEST_OBJS_DIR	= test_objs/
HEADER_DIR		= includes/

DIRS = $(addprefix $(OBJS_DIR), . builtins dummy_helpers pipex lst reading parser tests word_list)

# MAIN = $(SRCS_DIR)tests/simple_main.c
MAIN = $(SRCS_DIR)main.c
MAIN_OBJ := $(MAIN:$(SRCS_DIR)%.c=$(OBJS_DIR)%.o)

#		$(addprefix dummy_helpers/, fake_commands.c)
SRCS = $(addprefix $(SRCS_DIR), \
		$(addprefix dummy_helpers/, fake_commands.c debug.c) \
		$(addprefix pipex/, pipex.c path.c command.c utils.c file_redirection.c) \
		$(addprefix lst/, ft_lstcreate_addback.c ft_free_command.c ft_printf_list.c \
		ft_convert_word_list_to_list.c ft_make_redirect_list.c ft_printf_redirect.c ft_make_command_list.c \
		ft_free_redirects.c ft_free_command_list.c) \
		$(addprefix reading/, here_doc.c rl_gets.c) \
		$(addprefix parser/, parse.c missing_close.c \
		splitting.c flags.c quotes.c vars.c spaces.c flags_setting.c syntax_error.c \
		split_at_space.c make_word_list.c expand.c ft_strexchange.c wl_expansion.c free_str.c) \
		$(addprefix tests/, prints.c) \
		$(addprefix word_list/, word_list_methods.c word_list_methods2.c word_list_methods3.c word_desc.c) \
		$(addprefix builtins/ft_, cd.c echo.c pwd.c unset.c env.c exit.c export.c) \
		init_envp.c init_shell.c ft_free_shell.c signals.c ft_exchange_within.c\
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

run: all
	./$(NAME)

$(DIRS):
	mkdir -p $@

$(TEST_OBJS_DIR):
	@echo "Creating Test Obj directory.."
	@mkdir -p $(TEST_OBJS_DIR)

#-pie is used to generate position-independent code, new security feature
$(NAME): $(OBJS) $(LIBFT_A) $(MAIN_OBJ)
	@echo "Linking executable $(NAME)..."
	$(CC) $(CFLAGS) -I$(HEADERS) $(OBJS) $(MAIN_OBJ) $(INCLUDES) $(LIBFT) $(LIBS) -o $@ -pie
	@echo "done"

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c $(HEADERS) | $(DIRS)
	@$(CC) $(CFLAGS) -I$(HEADERS) -c $< -o $@

$(TEST_OBJS_DIR)%.o: $(SRCS_DIR)%.c $(HEADERS) | $(TEST_OBJS_DIR)
	@$(CC) $(CFLAGS) -I$(HEADERS) -c $< -o $@

LIBFT_DIR := libft

submodules:
	@mkdir -p $(LIBFT_DIR)
	@if [ -d "$(LIBFT_DIR)/.git" ]; then \
		echo "Initializing libft and its submodules..."; \
		git submodule add -q -f -b minishell git@github.com:Moat423/Libft_full.git $(LIBFT_DIR) || true; \
		git submodule update --init --recursive $(LIBFT_DIR); \
	elif [ -z "$$(ls -A $(LIBFT_DIR))" ]; then \
		echo "Updating libft and its submodules..."; \
		git submodule update --init --recursive --remote $(LIBFT_DIR); \
	fi
	@make -C $(LIBFT_DIR)
# submodules:
# 	@mkdir -p libft
# 	@if [ ! -d "$(LIBFT_DIR)" ] || [ -z "$$(ls -A $(LIBFT_DIR))" ]; then \
# 		echo "Initializing libft and its submodules..."; \
# 		git submodule add -q -f git@github.com:Moat423/Libft_full.git $(LIBFT_DIR); \
# 		git submodule update --init --recursive -- $(LIBFT_DIR); \
# 	else \
# 		echo "Updating libft and its submodules..."; \
# 		git submodule update --init --recursive -- $(LIBFT_DIR); \
# 	fi
# 	@make -s -C $(LIBFT_DIR) > /dev/null 2>&1

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
