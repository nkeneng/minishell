#include "../../includes/minishell.h"

int	get_number_of_words_before_pipe(t_word_list *word_list)
{
	int	number_of_words_before_pipe;

	number_of_words_before_pipe = 0;
	while (word_list)
	{
		if (word_list->word->flags & WM_OPERATOR_MASK)
			break ;
		number_of_words_before_pipe++;
		word_list = word_list->next;
	}
	return (number_of_words_before_pipe);
}

t_command	*make_command_list(t_word_list *word_list, t_word_list *curr)
{
	t_command	*command;
	int			number_of_words_before_pipe;

	(void)curr;
	number_of_words_before_pipe = 0;
	command = (t_command *)malloc(sizeof(t_command));
	number_of_words_before_pipe = get_number_of_words_before_pipe(word_list);
	command->cmd = (char **)malloc(sizeof(char *) * (number_of_words_before_pipe
				+ 1));
	command->cmd[number_of_words_before_pipe] = NULL;
	while (number_of_words_before_pipe--)
	{
		command->cmd[number_of_words_before_pipe] = ft_strdup(word_list->word->word);
		word_list_delone(&word_list, word_list);
	}
	curr = word_list;
	return (command);
}