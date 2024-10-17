/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeubrin <lmeubrin@student.42berlin.       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 12:44:56 by lmeubrin          #+#    #+#             */
/*   Updated: 2024/10/17 14:44:22 by lmeubrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_word_list	*split_for_var(char *line);

t_word_list	*split_at_squote(t_word_desc *element)
{
	t_word_list	*head;
	t_word_list	*item;
	t_command	*tmp_command;
	int			start;
	int			quote_start;
	int			end;

	head = NULL;
	start = 0;
	tmp_command = ft_calloc(sizeof(t_command), 1);
	while (element->word[start] != '\'')
	{
	}
	quote_start = start;
	if (!head)
		start = 0;
	head = ft_calloc(sizeof(t_word_list), 1);
	item = ft_calloc(sizeof(t_word_list), 1);
	return (head);
}

// makes a word and puts it inside word_desc from start of line to end
t_word_desc	*make_word(const char *line, const int end, const int flag)
{
	t_word_desc	*item;

	item = ft_calloc(sizeof(t_word_desc), 1);
	if (!item)
	{
		free(item);
		return (NULL);
	}
	item->word = ft_substr(line, 0, end);
	if (!item->word)
	{
		free_word_desc(item);
		return (NULL);
	}
	item->flags = flag;
	return (item);
}

//no need for this, just implement ft_is_var_name
t_word_list	*split_for_var(char *line)
{
	t_word_list	*head;
	t_word_desc	*word;
	int			i;
	int			start;

	i = 1;
	while (line[i] && line[i] != '=')
		i++;
	start = i;
	while (start >= 0 && line[start] != ' ')
		start--;
	while (line[i] && line[i] != ' ')
		i++;
	if (start)
	{
		word_list_addback(head, make_word(line, start, 0));
		if (!head)
			return (NULL);
	}
	word_list_addback(head, make_word(&line[start], i, W_VAR));
}
