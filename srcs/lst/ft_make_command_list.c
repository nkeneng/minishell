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
		if (tmp->word->flags & W_SPLITSPACE || !tmp->next || tmp->next->word->flags & WM_OPERATOR_MASK)
			number_of_words_before_pipe++;
		tmp = tmp->next;
	}
	if (!tmp->next)
			number_of_words_before_pipe++;
	return (number_of_words_before_pipe);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len1;
	size_t	len2;
	char	*joined_str;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	joined_str = (char *) malloc(len1 + len2 + 1);
	if (!joined_str)
		return (NULL);
	ft_strlcpy(joined_str, s1, len1 + 1);
	ft_strlcpy(joined_str + len1, s2, len2 + 1);
	joined_str[len1 + len2 + 1] = '\0';
	return (joined_str);
}

t_command	*make_command_list(t_word_list **word_list)
{
	t_command	*command;
	int			wordcount_till_pipe;
	int i = 0;
	t_word_list	*tmp;

	if(!word_list)
		return (NULL);
	wordcount_till_pipe = 0;
	command = (t_command *)ft_calloc(sizeof(t_command), 1);
	if (!command)
		return (NULL);
	wordcount_till_pipe = get_number_of_words_before_pipe(*word_list);
	command->cmd = (char **)malloc(sizeof(char *) * (wordcount_till_pipe + 1));
	if (!command->cmd)
	{
		free(command);
		return (NULL);
	}
	tmp = *word_list;
	while (i < wordcount_till_pipe)
	{
		if (command->cmd[i] && (tmp->prev && tmp->prev->word->flags & ~W_SPLITSPACE))
			command->cmd[i] = ft_strjoin(command->cmd[i], tmp->word->word);
		else
			command->cmd[i] = ft_strdup(tmp->word->word);
		if (tmp->word->flags & W_SPLITSPACE || !tmp->next || tmp->next->word->flags & WM_OPERATOR_MASK)
			i++;
		// TODO: free if !command->cmd[i]
		command->flags += (*word_list)->word->flags;
		wl_delone(word_list, tmp);
		tmp = *word_list;
	}
	wl_delone(word_list, tmp); // remove the pipe
	command->cmd[i] = NULL;
	return (command);
}
