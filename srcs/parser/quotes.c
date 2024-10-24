/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeubrin <lmeubrin@student.42berlin.       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 12:44:56 by lmeubrin          #+#    #+#             */
/*   Updated: 2024/10/24 14:28:07 by lmeubrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_word_list	*split_for_var(char *line);
t_word_list	*wordlist_from_line(t_word_list *h, char *line, int size, int flag);

// returns the i that it stopped at, fills to_fill with content from line
// until it hits a valid delim (|, <, >, "", '', ' ')
// or until the next one of that kind is hit
int	fill_with_token(char *line, t_word_desc *to_fill)
{
	int	i;

	i = 0;
	if (!sign_to_flag(line))
	{
		while (!sign_to_flag(&line[i]))
			i++;
	}
	else
		i = next_word_till(line, line[0]);
	to_fill = make_word(line, i, sign_to_flag(line));
	return (i);
}

t_word_list	*split_at_quote(char *line)
{
	t_word_list	*head;
	t_word_list	*item;
	int			st;
	int			i;

	head = NULL;
	i = 1;
	st = 0;
	while (line[st])
	{
		while (line[st] && (line[st] != '\'' || line[st] != '"'))
			st++;
		if (st)
			item = wordlist_from_line(head, line, st, 0);
		if (!item)
			return (NULL);
		while (line[st + i] != line[st])
			i++;
		item = wordlist_from_line(head, &line[st], i, sign_to_flag(&line[st]));
		if (!item)
			return (NULL);
		st = i + 1;
	}
	return (head);
}

// returns head, and if head NULL, error occured and list was freed.
// puts string with size inside t_word_desc and adds that to the end of the list
t_word_list	*wordlist_from_line(t_word_list *h, char *line, int size, int flag)
{
	t_word_list	*item;
	t_word_desc	*desc;

	desc = make_word(line, size, flag);
	if (!desc)
		return (NULL);
	item = word_list_addback(h, desc);
	if (!item)
		free_word_list(&h);
	return (h);
}

//no need for this, just implement ft_is_var_name
t_word_list	*split_for_var(char *line)
{
	t_word_list	*head;
	int			i;
	int			start;

	i = 1;
	head = NULL;
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
	return (head);
}
