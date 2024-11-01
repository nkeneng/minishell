/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_list1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeubrin <lmeubrin@student.42berlin.       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 12:43:51 by lmeubrin          #+#    #+#             */
/*   Updated: 2024/10/28 14:39:55 by lmeubrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_word_list	*make_word_list(char *line)
{
	t_word_list	*word_list_head;
	t_word_list	*word_list;

	word_list_head = init_word_list(line);
	word_list = (split_around(word_list_head->word));
	if (!word_list || !word_list->word)
		return (NULL);
	free_word_list(&word_list_head);
	return (word_list);
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
