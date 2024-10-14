
#include "../../includes/minishell.h"

//cc -Werror -Wall -Wextra -g  srcs/parser/word_list1.c srcs/parser/word_list2.c libft/libft.a

int	main(void)
{
	char		*input;
	char		hardstring[] = "Hello%||^mynopspace|pipe";
	t_word_list	*word_list;

	input = ft_substr(hardstring, 0, ft_strlen(hardstring));
	word_list = make_word_list(input);
	ft_printf_word_list(word_list);
	free(input);
	free_word_list(&word_list);
}
