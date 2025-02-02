/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_make_redirect_list.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeubrin <lmeubrin@student.42berlin.       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 12:25:08 by lmeubrin          #+#    #+#             */
/*   Updated: 2025/02/02 19:46:19 by lmeubrin         ###   ########.fr       */
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

static void	free_word_a_redirect(t_word_list **list, t_list **redir)
{
	ft_lstclear(redir, ft_free_redirect);
	free_word_list(list);
	list = NULL;
	ft_lstclear(redir, free);
	return ;
}

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
		if (curr->next == NULL)
			return (free_on_syn_err(list, "newline", &redir_head));
		if (curr->next->word->flags & WM_OP_RE)
			return (free_on_syn_err(list, curr->next->word->word, &redir_head));
		curr->next->word->flags |= curr->word->flags;
		while (curr->next->next && !(curr->next->next->word->flags & WM_OPERATOR_MASK) && !(curr->next->word->flags & W_SPLITSPACE))
			if (fuse_words(list, curr->next->next))
				free_word_a_redirect(list, &redir_head);
		redir_item = wl_to_redirect(list, curr->next);
		ft_lstadd_back(&redir_head, ft_lstnew(redir_item));
		next = curr->next;
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
