/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_make_command_list.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeubrin <lmeubrin@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 12:27:50 by lmeubrin          #+#    #+#             */
/*   Updated: 2025/02/03 11:56:51 by lmeubrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	get_number_of_words_before_pipe(t_word_list *word_list)
{
	int			number_of_words_before_pipe;
	t_word_list	*tmp;

	number_of_words_before_pipe = 0;
	tmp = word_list;
	if (!tmp)
		return (0);
	while (tmp->next)
	{
		if (tmp->word->flags & WM_OPERATOR_MASK)
			break ;
		if (tmp->word->flags & W_SPLITSPACE || !tmp->next
			|| tmp->next->word->flags & WM_OPERATOR_MASK)
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
	joined_str = (char *)malloc(len1 + len2 + 1);
	if (!joined_str)
		return (NULL);
	ft_strlcpy(joined_str, s1, len1 + 1);
	ft_strlcpy(joined_str + len1, s2, len2 + 1);
	joined_str[len1 + len2] = '\0';
	return (joined_str);
}

void	ft_assign_flag_builtin(t_command *command)
{
	if (is_builtin(command->cmd[0]))
		command->flags |= C_BUILTIN;
}

t_command	*fill_command(int wdcnt_to_pipe, t_command *cmd, t_word_list **wlst)
{
	t_word_list	*tmp;
	int			i;

	i = 0;
	tmp = *wlst;
	while (i < wdcnt_to_pipe)
	{
		if (cmd->cmd[i])
			cmd->cmd[i] = ft_freejoin(cmd->cmd[i], tmp->word->word);
		else
			cmd->cmd[i] = ft_strdup(tmp->word->word);
		if (tmp->word->flags & W_SPLITSPACE || !tmp->next
			|| tmp->next->word->flags & WM_OPERATOR_MASK)
			i++;
		cmd->flags |= (*wlst)->word->flags;
		wl_delone(wlst, tmp);
		tmp = *wlst;
	}
	wl_delone(wlst, tmp);
	cmd->cmd[i] = NULL;
	ft_assign_flag_builtin(cmd);
	return (cmd);
}

t_command	*make_command_list(t_word_list **word_list)
{
	t_command	*command;
	int			wordcount_till_pipe;

	if (!word_list)
		return (NULL);
	wordcount_till_pipe = 0;
	command = (t_command *)ft_calloc(sizeof(t_command), 1);
	if (!command)
		return (NULL);
	wordcount_till_pipe = get_number_of_words_before_pipe(*word_list);
	if (!wordcount_till_pipe)
	{
		free(command);
		return (NULL);
	}
	command->cmd = (char **)ft_calloc(sizeof(char *), (wordcount_till_pipe
				+ 1));
	if (!command->cmd)
	{
		free(command);
		return (NULL);
	}
	return (fill_command(wordcount_till_pipe, command, word_list));
}
