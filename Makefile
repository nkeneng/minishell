NAME = project

CC = cc

CFLAGS = -Wall -Werror -Wextra -g

SRCS_DIR		= ./sources/
OBJS_DIR		= ./objs/

SRCS = main.c

# TEST_SRCS = $(filter-out main.c, $(SRCS))
# TESTS_FILES = $(shell find ./test -name "*_test.c")

LIBFT = -Llibft -lft

OBJS = $(patsubst $(SRCS_DIR)%.c,$(OBJS_DIR)%.o,$(SRCS))
# TEST_OBJS = $(TESTS_FILES:.c=.o)

all: submodules libft $(NAME)

run: all
	./$(NAME)

submodules:
	if [ ! -d "libft" ]; then \
		mkdir libft; \
	fi
	if [ -z "$(shell ls -A libft)" ]; then \
		echo "libft submodule not initialized, initializing..."; \
		git submodule init && git submodule update --recursive; \
	fi
	if [ -z "$(shell ls -A libft/ft_printf)" -o -z "$(shell ls -A libft/get_next_line)" ]; then \
		echo "libft submodule not initialized, initializing..."; \
		cd libft && git submodule init && git submodule update --recursive; \
	fi

libft:
	$(MAKE) -C libft

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)

# test: $(TEST_SRCS:.c=.o) $(TEST_OBJS)
# 	$(CC) $(CFLAGS) $(TEST_SRCS:.c=.o) $(TEST_OBJS) $(LIBFT) -lcriterion -o test.out && ./test.out

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJS) $(OBJS_DIR)
	$(MAKE) -C libft clean
	# rm -f $(TEST_SRCS:.c=.o) $(TEST_OBJS)

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C libft fclean
	# rm -f test.out

re: fclean all

.PHONY: all clean fclean re submodules libft test
