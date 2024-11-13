/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeubrin <lmeubrin@student.42berlin.       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 12:44:56 by lmeubrin          #+#    #+#             */
/*   Updated: 2024/11/11 20:22:09 by lmeubrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// function removes beginning and ending quotes from word
// param: word_desc with flag W_SQUOTED or W_DQUOTED
// returns word_desc
t_word_desc	*remove_quotes(t_word_desc *word)
{
	int		len;
	char	*end_string;
	int		len_end;

	if (!(word->flags & W_SQUOTED || word->flags & W_DQUOTED))
		return (word);
	len = ft_strlen(word->word);
	end_string = ft_strrchr(word->word, word->word[0]);
	len_end = ft_strlen(end_string);
	ft_bzero(end_string, len_end);
	ft_memmove(word->word, word->word + 1, len - len_end);
	return (word);
}

// NOT USING THE FOLLOWING TWO FUNCITONS I THINK
// returns the i that it stopped at, fills to_fill with content from line
// until it hits a valid delim (|, <, >, "", '', ' ')
// or until the next one of that kind is hit
int	fill_with_token(char *line, t_word_list *to_fill)
{
	int	i;
	t_word_desc *desc;

	i = 0;
	if (!sign_to_flag(line))
	{
		while (!sign_to_flag(&line[i]))
			i++;
	}
	else
		i = next_word_till(line, line[0]);
	desc = wd_make_word(line, i, sign_to_flag(line));
	to_fill->word = desc;
	return (i);
}

t_word_list	*split_at_quote(char *line)
{
	t_word_list	*head;
	t_word_list	*item;
	int			st;
	int			i;
	int			flag;

	head = NULL;
	i = 1;
	st = 0;
	while (line[st])
	{
		while (line[st] && (line[st] != '\'' || line[st] != '"'))
			st++;
		if (st)
			item = wl_from_line(head, line, st, 0);
		if (!item)
			return (NULL);
		while (line[st + i] != line[st])
			i++;
		flag = sign_to_flag(&line[st]);
		if (ft_whitespace_seperator(&line[st + i + 1]))
		{
			line[st + i++] = ' ';
			flag |= W_SPLITSPACE;
		}
		item = wl_from_line(head, &line[st], i, flag);
		if (!item)
			return (NULL);
		st = i + 1;
	}
	return (head);
}
