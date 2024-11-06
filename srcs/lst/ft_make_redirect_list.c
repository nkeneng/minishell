/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_redirect_list.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeubrin <lmeubrin@student.42berlin.       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 12:25:08 by lmeubrin          #+#    #+#             */
/*   Updated: 2024/11/06 15:42:53 by lmeubrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// takes list of words and makes a list of redirects
t_list	*make_redirect_list(t_word_list **list)
{
	t_word_list		*curr;
	t_list			*redir_head;
	t_word_desc		*word_to_add;
	t_word_list		*next;

	redir_head = NULL;
	curr = *list;
	while (curr)
	{
		curr = find_redir(curr);
		if (!curr)
			break ;
		if (curr->next == NULL)
		{
			syntax_error(*list, curr->word->word);
			free_word_list(list);
			ft_lstclear(&redir_head, free);
			return (NULL);
		}
		word_to_add = word_list_unlink(list, curr->next); //run clean spaces on that
		ft_lstadd_back(&redir_head, ft_lstnew(word_to_add));
		next = curr->next;
		word_list_delone(list, curr);
		curr = next;
	}
	return (redir_head);
}

// finds next redirect in list
t_word_list	*find_redir(t_word_list *list)
{
	t_word_desc	*curr_item;

	while (list)
	{
		curr_item = list->word;
		if (curr_item->flags & WM_REDIR_MASK)
			return (list);
		if (curr_item->flags & WM_OPERATOR_MASK)
			return (NULL);
		list = list->next;
	}
	return (NULL);
}
