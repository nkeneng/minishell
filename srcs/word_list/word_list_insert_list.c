/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_list_insert_list.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeubrin <lmeubrin@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 14:51:52 by lmeubrin          #+#    #+#             */
/*   Updated: 2024/11/11 14:59:21 by lmeubrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "includes/parsing.h"
#include "includes/redirect.h"

// takes a word_list and inserts head of element in place of to_delete.
// last element of list starting with head gets connected to to_delete->next
// returns the last element that was inserted
t_word_list	*word_list_insert_list(t_word_list *head, t_word_list *to_delete)
{
	t_word_list	*last;
	
	if (!head || !to_delete)
		return (NULL);
	last = head;
	while (last->next)
		last = last->next;
	if (to_delete->prev)
		to_delete->prev->next = head;
	head->prev = to_delete->prev;
	if (to_delete->next)
		to_delete->next->prev = last;
	last->next = to_delete->next;
	free_word_desc(to_delete->word);
	free(to_delete);
	return (last);
}
