/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_at_space.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeubrin <lmeubrin@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 17:07:48 by lmeubrin          #+#    #+#             */
/*   Updated: 2025/01/09 10:42:45 by lmeubrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_word_list	*helper_split(t_word_list *item, int sep, t_word_list *curr)
{
	t_word_desc	*new_item;
	int			i;
	int			begin_word;

	i = sep;
	begin_word = i;
	while (item->word->word[i])
	{
		sep = ft_whitespace_seperator(&item->word->word[i]);
		if (sep)
		{
			i += sep;
			new_item = wd_make_word(&item->word->word[begin_word], i
					- begin_word, item->word->flags);
			curr = wl_insert(curr, new_item);
			if (!curr)
				return (NULL);
			begin_word = i;
		}
		i++;
	}
	return (curr);
}

t_word_list	*split_at_spaces(t_word_list *item)
{
	int	s;

	if (item->word->flags & W_SQUOTED || item->word->flags & W_DQUOTED)
		return (NULL);
	s = ft_whitespace_seperator(&item->word->word[0]);
	return (helper_split(item, s, item));
}

int	seperate_words_in_line(char *line, int flags, int i, t_word_list **head)
{
	int			begin_word;
	int			s;

	begin_word = i;
	while (line[i])
	{
		s = ft_whitespace_seperator(&line[i]);
		if (s)
		{
			if (!wl_add_node(head, &line[begin_word], i - begin_word,
					flags | W_SPLITSPACE))
				return (-1);
			i += s;
			begin_word = i;
			continue ;
		}
		else
			i++;
	}
	return (begin_word);
}

// takes a line and splits the line at whitespaces and puts them
// into word_desc items and concats them into a word_list
t_word_list	*word_list_ft_split(char *line, int flags)
{
	int			i;
	int			begin_word;
	t_word_list	*head;

	i = ft_skip_whitespace(line);
	head = NULL;
	begin_word = seperate_words_in_line(line, flags, i, &head);
	if (begin_word == -1)
		return (NULL);
	i = ft_strlen(line);
	if (begin_word != i)
		if (!wl_add_node(&head, &line[begin_word], i - begin_word, flags))
			return (NULL);
	return (head);
}
