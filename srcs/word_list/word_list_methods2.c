/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_list_methods2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeubrin <lmeubrin@student.42berlin.       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 14:58:56 by lmeubrin          #+#    #+#             */
/*   Updated: 2024/11/06 12:56:19 by lmeubrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


// deletes a single word_list item and reconnects the list
void	word_list_delone(t_word_list **head, t_word_list *to_remove)
{
	if (!head || !to_remove)
		return ;
	if (*head == to_remove)
		*head = to_remove->next;
	if (to_remove->prev)
		to_remove->prev->next = to_remove->next;
	if (to_remove->next)
		to_remove->next->prev = to_remove->prev;
	if (to_remove->word)
		free_word_desc(to_remove->word);
	free(to_remove);
}

void	word_list_insert_word_list(t_word_list *head_to_insert, t_word_list *insert_after)
{
    t_word_list *next_element;
    t_word_list *last;

    if (!head_to_insert || !insert_after)
    {
        return ;
    }
	next_element = insert_after->next;
    insert_after->next = head_to_insert;
    head_to_insert->prev = insert_after;
	last = head_to_insert;
    while (last->next)
        last = last->next;
    last->next = next_element;
    if (next_element)
        next_element->prev = last;
}
