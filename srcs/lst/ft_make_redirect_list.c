/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_redirect_list.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeubrin <lmeubrin@student.42berlin.       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 12:25:08 by lmeubrin          #+#    #+#             */
/*   Updated: 2024/11/10 12:02:02 by lmeubrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// takes list of words and makes a list of redirects
t_list	*make_redirect_list(t_word_list **list)
{
	t_word_list		*curr;
	t_list			*redir_head;
	t_redirect		*redir_item;
	t_word_list		*next;

	redir_head = NULL;
	curr = *list;
	while (curr)
	{
		curr = find_redir(curr);
		if (!curr)
			break ;
		next = curr->next;
		if (curr->next == NULL || (next->word->flags & (WM_OPERATOR_MASK | WM_REDIR_MASK)))
		{
			if (curr->next == NULL)
				syntax_error(list, curr->word->word);
			else
				syntax_error(list, next->word->word);
			free_word_list(list);
			list = NULL;
			ft_lstclear(&redir_head, free);
			return (NULL);
		}
		redir_item = wl_to_redirect(list, next);
		wd_remove_whitespace(redir_item->filename);
		ft_lstadd_back(&redir_head, ft_lstnew(redir_item));
		wl_delone(list, curr);
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
