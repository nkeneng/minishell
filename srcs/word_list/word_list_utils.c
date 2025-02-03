/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_list_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeubrin <lmeubrin@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 11:59:44 by lmeubrin          #+#    #+#             */
/*   Updated: 2025/02/03 12:10:44 by lmeubrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	free_word_a_redirect(t_word_list **list, t_list **redir)
{
	ft_lstclear(redir, ft_free_redirect);
	free_word_list(list);
	list = NULL;
	ft_lstclear(redir, free);
	return ;
}

// fuses a word with the next word, if the curr word does'nt have splitspace
// return 0 upon success, 1 upon failure
// frees all memory if failure
int	wl_fuse_nosplit(t_word_list **lst, t_list **red, t_word_list *cur)
{
	while (cur->next->next && !(cur->next->next->word->flags & \
		WM_OPERATOR_MASK) && !(cur->next->word->flags & W_SPLITSPACE))
	{
		if (fuse_words(lst, cur->next->next))
		{
			free_word_a_redirect(lst, red);
			return (1);
		}
	}
	return (0);
}

// deletes one word from word_list
// returns the next word
t_word_list	*wl_removeone(t_word_list **list, t_word_list *curr)
{
	t_word_list	*next;

	next = curr->next;
	wl_delone(list, curr);
	return (next);
}
