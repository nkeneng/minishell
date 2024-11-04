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

t_word_list	*find_redir(t_word_list *list);

// takes single t_word_desc and turns it into a t_redirectee
t_redirectee	*make_redirectee_from_word_desc(t_word_desc *item)
{
	t_redirectee	*redir;

	return (redir);
}

t_redirect	*make_redirect_list(t_word_list **list)
{
	t_word_list		*curr;
	t_redirect		*redir_head;
	t_redirect		*redir_item;
	t_redirectee	*redir_union;

	curr = *list;
	redir_head = malloc(sizeof(t_redirect));
	while (curr)
	{
		curr = find_redir(curr);
		redir_union = make_redirectee_from_word_desc(curr->word);
		word_list_delone(curr);
	}
	return (redir_head);
}

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

// takes current redirect list item and adds content as redirectee of curr and
// makes new redirect list item and makes content the redirector this item
// returns pointer to new and added list item
t_redirect	*redirect_addafter(t_redirect *list, t_redirectee *content)
{
	t_redirect	*new;

	if (!content)
		return (NULL);
	new = malloc(sizeof(t_redirect));
	if (!new)
		return (NULL);
	new->redirector = *content;
	new->next = NULL;
	if (!list)
	{
		list = new;
		return (new);
	}
	list->next = new;
	return (new);
}
