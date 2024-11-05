/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversion_wordlist_list.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeubrin <lmeubrin@student.42berlin.       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 12:25:08 by lmeubrin          #+#    #+#             */
/*   Updated: 2024/11/04 16:52:29 by lmeubrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// takes list of words and makes a list of redirects
t_list	*make_redirect_list(t_word_list **list)
{
	t_word_list		*curr;
	t_list			*redir_head;

	redir_head = NULL;
	curr = *list;
	while (curr)
	{
		curr = find_redir(curr);
		if (!curr->next)
			syntax_error(*list, curr->word->word);
		ft_lstadd_back(&redir_head, ft_lstnew(curr->next->word));
		word_list_delone(curr);
		word_list_delone(curr->next);
	}
	return (redir_head);
}

// finds next redirect in list
t_word_list	*find_redir(t_word_list *list)
{
	t_word_desc	*curr_item;

	while (list && !(list->word->flags & WM_REDIR_MASK))
	{
		curr_item = list->word;
		if (is_pipe_or_redirect(curr_item->word))
			return (NULL);
		list = list->next;
	}
	return (list);
}