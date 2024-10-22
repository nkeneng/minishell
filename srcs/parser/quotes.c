/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeubrin <lmeubrin@student.42berlin.       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 12:44:56 by lmeubrin          #+#    #+#             */
/*   Updated: 2024/10/22 16:32:51 by lmeubrin         ###   ########.fr       */
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
	{
		start++;
	}
	quote_start = start;
	if (!head)
		start = 0;
	head = ft_calloc(sizeof(t_word_list), 1);
	item = ft_calloc(sizeof(t_word_list), 1);
	return (head);
}

t_word_list	*split_at_quote(char *line)
{
	t_word_list	*head;
	t_word_list	*item;
	int			i;

	i = 0;
	if (!line[0])
		return (NULL);
	while (line [i] && line[i] != '\'' || line[i] != '"')
		i++;
	if (i)
		head = wordlist_from_line(head, line, i, 0);
	else
		
	return (head);
}

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
