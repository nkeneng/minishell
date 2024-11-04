/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_list_methods2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeubrin <lmeubrin@student.42berlin.       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 14:58:56 by lmeubrin          #+#    #+#             */
/*   Updated: 2024/11/04 15:26:53 by lmeubrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//uses prev pointer to delete a single word_list item and reconnect ne one after
void	word_list_delone(t_word_list *to_remove)
{
	t_word_list	*item;

	item = to_remove->prev;
	item->next = to_remove->next;
	item = to_remove->next;
	item->prev = to_remove->prev;
	free_word_desc(to_remove->word);
	free(to_remove);
}

/* void	word_list_insert_word_list(t_word_list *item) */
