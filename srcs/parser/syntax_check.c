/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeubrin <lmeubrin@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 13:30:47 by lmeubrin          #+#    #+#             */
/*   Updated: 2024/11/22 10:19:43 by lmeubrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// performs syntax checks on list:
// 1. checks if operator is followed by another operator or newline
// 2. checks if redirection operator is followed by another redirection operator
// or operator or newline
// returns 0 if no syntax errors found
int	wl_syntax_check(t_word_list **head)
{
	t_word_list	*curr;

	curr = *head;
	while (curr)
	{
		if (curr->word->flags & WM_OPERATOR_MASK)
		{
			if (!(curr->next))
				syntax_error(head, "newline");
			if (curr->next->word->flags & WM_OPERATOR_MASK)
				syntax_error(head, curr->next->word->word);
		}
		if (curr->word->flags & ~W_EXPANDED && \
			WM_REDIR_MASK & identify_word_type(curr->word))
		{
			if (!(curr->next))
				syntax_error(head, "newline");
			if (curr->next->word->flags & WM_OPERATOR_MASK && \
			WM_REDIR_MASK & identify_word_type(curr->next->word))
				syntax_error(head, curr->next->word->word);
		}
		curr = curr->next;
	}
	return (0);
}
