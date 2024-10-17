/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_list1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeubrin <lmeubrin@student.42berlin.       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 12:43:51 by lmeubrin          #+#    #+#             */
/*   Updated: 2024/10/17 18:01:32 by lmeubrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_word_list	*make_word_list(char *line)
{
	t_word_list	*word_list_head;
	t_word_list	*word_list;
	t_word_list	*tmp;
	int			i;

	word_list = split_at_pipes(line);
	if (!word_list || !word_list->word)
		return (NULL);
	word_list_head = word_list;
	i = strlen(word_list->word->word);
	while (line[i])
	{
		tmp = split_at_pipes(&line[i]);
		if (!tmp)
		{
			free_word_list(&word_list_head);
			return (NULL);
		}
		word_list->next = tmp;
		word_list = tmp;
		i += strlen(word_list->word->word);
	}
	return (word_list_head);
}

t_word_list	*split_at_pipes(char *line)
{
	int			i;
	char		*substr;
	t_word_list	*word;
	int			flag;

	if (!line)
		return (NULL);
	flag = W_PIPE;
	i = 0;
	if (line[i] == '|')
		while (line[i] == '|')
			i++;
	else
		while (line[i] && '|' != line[i])
			i++;
	substr = ft_substr(line, 0, i);
	if (!substr)
		return (NULL);
	word = ft_calloc(sizeof(t_word_list), 1);
	if (!word)
		return (NULL);
	word->word = create_word(substr, flag);
	if (!word->word)
		return (NULL);
	return (word);
}

t_word_list	*make_word_list_new(char *line)
{
	t_word_list	*word_list_head;
	t_word_list	*word_list;

	word_list_head = init_word_list(line);
	word_list = (split_after(word_list_head->word, '|'));
	if (!word_list || !word_list->word)
		return (NULL);
	free_word_list(&word_list_head);
	return (word_list);
}
