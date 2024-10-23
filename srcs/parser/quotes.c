/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeubrin <lmeubrin@student.42berlin.       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 12:44:56 by lmeubrin          #+#    #+#             */
/*   Updated: 2024/10/23 17:15:30 by lmeubrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_word_list	*split_for_var(char *line);
t_word_list	*wordlist_from_line(t_word_list *h, char *line, int size, int flag);

t_word_list	*split_at_squote(t_word_desc *element)
{
	t_word_list	*head;
	t_word_list	*item;
	int			start;
	int			quote_start;
	int			end;

	head = NULL;
	start = 0;
	while (element->word[start] != '\'')
		start++;
	quote_start = start;
	if (!head)
		start = 0;
	head = ft_calloc(sizeof(t_word_list), 1);
	item = ft_calloc(sizeof(t_word_list), 1);
	return (head);
}

// returns the i that it stopped at, fills to_fill with content from line 
// until it hits a valid delim (|, <, >, "", '')
// or until the next one of that kind is hit
int	fill_with_token(char *line, t_word_desc *to_fill)
{
	int	i;
	
	i = 0;
	if (!sign_to_flag(line[0]))
	{
		while (!sign_to_flag(line[i]))
			i++;
	}
	else
		i = next_word_till(line, line[0]);
	to_fill = make_word(line, i, sign_to_flag(line[0]));
	return (i);
}

t_word_list	*split_at_quote(char *line)
{
	t_word_list	*head;
	t_word_list	*item;
	int			start;
	int			i;
	int			sign;

	head = NULL;
	i = 1;
	start = 0;
	while (line[start])
	{
		while (line[start] && line[start] != '\'' || line[start] != '"')
			start++;
		sign = line[start];
		if (start)
			item = wordlist_from_line(head, line, start, 0);
		if (!item)
			return (NULL);
		while (line[start + i] != sign)
			i++;
		item = wordlist_from_line(head, &line[start], i, sign_to_flag(sign));
		if (!item)
			return (NULL);
		start = i + 1;
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
	return (head);
}
