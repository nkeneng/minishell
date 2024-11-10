#include "../../includes/minishell.h"

int	get_number_of_words_before_pipe(t_word_list *word_list)
{
	int	number_of_words_before_pipe;
	t_word_list	*tmp;

	number_of_words_before_pipe = 0;
	tmp = word_list;
	while (tmp->next)
	{
		if (tmp->word->flags & WM_OPERATOR_MASK)
			break ;
		number_of_words_before_pipe++;
		tmp = tmp->next;
	}
	return (number_of_words_before_pipe);
}

t_command	*make_command_list(t_word_list *word_list, t_word_list *curr)
{
	t_command	*command;
	int			number_of_words_before_pipe;
	int i = 0;
	t_word_list	*tmp;

	(void)curr;
	number_of_words_before_pipe = 0;
	command = (t_command *)malloc(sizeof(t_command));
	number_of_words_before_pipe = get_number_of_words_before_pipe(word_list);
	command->cmd = (char **)malloc(sizeof(char *) * (number_of_words_before_pipe
				+ 1));
	tmp = word_list;
	while (i < number_of_words_before_pipe)
	{
		ft_printf("word_list->word->word : %s\n", word_list->word->word);
		command->cmd[i] = ft_strdup(word_list->word->word);
		word_list_delone(&word_list, tmp);
		tmp = word_list;
		i++;
	}
	word_list_delone(&word_list, tmp); // remove the pipe
	command->cmd[i] = NULL;
	curr = word_list;
	return (command);
}
