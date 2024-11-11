/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_at_space.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeubrin <lmeubrin@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 17:07:48 by lmeubrin          #+#    #+#             */
/*   Updated: 2024/11/11 18:28:33 by lmeubrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_word_list	*split_at_spaces(t_word_list *item)
{
	t_word_desc	*new_item;
	t_word_list	*curr;
	int			i;
	int			begin_word;
	int			s;

	if (item->word->flags & W_SQUOTED || item->word->flags & W_DQUOTED)
		return (NULL);
	s = ft_whitespace_seperator(&item->word->word[0]);
	i = s;
	begin_word = i;
	curr = item;
	while (item->word->word[i])
	{
		s = ft_whitespace_seperator(&item->word->word[i]);
		if (s)
		{
			i += s;
			new_item = make_word(&item->word->word[begin_word], i - begin_word, item->word->flags);
			curr = word_list_insert(curr, new_item);
			if (!curr)
				return (NULL);
			begin_word = i;
		}
		i++;
	}
	return (curr);
}

// takes a line and splits the line at whitespaces and puts them 
// into word_desc items and concats them into a word_list
t_word_list	*word_list_ft_split(char *line)
{
	int			i;
	int			begin_word;
	int			s;
	t_word_desc	*new_item;
	t_word_list	**head;
	t_word_list	*curr;

	i = ft_skip_whitespace(line);
	begin_word = i;
	curr = NULL;
	head = &curr;
	while (line[i])
	{
		s = ft_whitespace_seperator(&line[i]);
		if (s)
		{
			i += s;
			new_item = make_word(&line[begin_word], i - begin_word, 0);
			ft_printf("new_item->word: \"%s\"\n", new_item->word);
			curr = word_list_addback(head, new_item);
			ft_printf_word_list(*head);
			ft_printf_word_list(curr);
			if (!curr)
			{
				free_word_list(head);
				return (NULL);
			}
			begin_word = i;
		}
		i++;
	}
	return (*head);
}
