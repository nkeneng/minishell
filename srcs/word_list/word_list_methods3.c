/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_list_methods3.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeubrin <lmeubrin@student.42berlin.       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 12:43:51 by lmeubrin          #+#    #+#             */
/*   Updated: 2025/01/09 07:39:41 by lmeubrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// returns head, and if head NULL, error occured and list was freed.
// puts string with size inside t_word_desc and adds that to the end of the list
t_word_list	*wl_from_line(t_word_list *h, char *line, int size, int flag)
{
	t_word_list	*item;
	t_word_desc	*desc;

	desc = wd_make_word(line, size, flag);
	if (!desc)
		return (NULL);
	item = wl_addback(h, desc);
	if (!item)
		free_word_list(&h);
	return (h);
}

// remove_whitespace_element and sets flags for previous item to have had space
t_word_list	*wl_remove_whitespace_element(t_word_list **head, t_word_list *curr)
{
	int			i;

	i = ft_skip_whitespace(curr->word->word);
	if (i && curr->word->word[i] == '\0')
	{
		if (curr->prev)
			curr->prev->word->flags |= W_SPLITSPACE;
		curr = wl_delone(head, curr);
	}
	return (curr);
}

// inserts a word list called new_lst after a word list element called after
// returns the last element of the inserted list
t_word_list	*wl_insert_word_list(t_word_list *new_lst, t_word_list *after)
{
	t_word_list	*next_element;
	t_word_list	*last;

	if (!new_lst || !after)
		return (NULL);
	next_element = after->next;
	after->next = new_lst;
	new_lst->prev = after;
	last = new_lst;
	while (last->next)
		last = last->next;
	last->next = next_element;
	if (next_element)
		next_element->prev = last;
	return (last);
}
