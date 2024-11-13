/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_at_space.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeubrin <lmeubrin@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 17:07:48 by lmeubrin          #+#    #+#             */
/*   Updated: 2024/11/12 14:59:21 by lmeubrin         ###   ########.fr       */
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
			new_item = wd_make_word(&item->word->word[begin_word], i - begin_word, item->word->flags);
			curr = wl_insert(curr, new_item);
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
	t_word_list	*head;

	i = ft_skip_whitespace(line);
	begin_word = i;
	head = NULL;
	while (line[i])
	{
		s = ft_whitespace_seperator(&line[i]);
		if (s)
		{
			if (!wl_add_node(&head, &line[begin_word], i - begin_word, W_SPLITSPACE))
				return (NULL);
			i += s;
			begin_word = i;
			continue ;
		}
		i++;
	}
	if (!wl_add_node(&head, &line[begin_word], i - begin_word, 0))
		return (NULL);
	return (head);
}
