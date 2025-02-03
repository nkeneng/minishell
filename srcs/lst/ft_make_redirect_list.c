/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_make_redirect_list.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeubrin <lmeubrin@student.42berlin.       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 12:25:08 by lmeubrin          #+#    #+#             */
/*   Updated: 2025/02/03 12:08:45 by lmeubrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	*free_on_syn_err(t_word_list **list, char *desc, t_list **redir)
{
	syntax_error(list, desc);
	ft_lstclear(redir, ft_free_redirect);
	free_word_list(list);
	list = NULL;
	ft_lstclear(redir, free);
	return (NULL);
}

// takes list of words and makes a list of redirects
t_list	*make_redirect_list(t_word_list **list)
{
	t_word_list		*curr;
	t_list			*redir_head;
	t_redirect		*redir_item;

	redir_head = NULL;
	curr = *list;
	while (curr)
	{
		curr = find_redir(curr);
		if (!curr)
			break ;
		if (curr->next == NULL)
			return (free_on_syn_err(list, "newline", &redir_head));
		if (curr->next->word->flags & WM_OP_RE)
			return (free_on_syn_err(list, curr->next->word->word, &redir_head));
		curr->next->word->flags |= curr->word->flags;
		if (wl_fuse_nosplit(list, &redir_head, curr))
			return (NULL);
		redir_item = wl_to_redirect(list, curr->next);
		ft_lstadd_back(&redir_head, ft_lstnew(redir_item));
		curr = wl_removeone(list, curr);
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
