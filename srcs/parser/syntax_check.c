/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeubrin <lmeubrin@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 13:30:47 by lmeubrin          #+#    #+#             */
/*   Updated: 2024/11/20 14:27:14 by lmeubrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	wl_syntax_check(t_word_list **head)
{
	t_word_list	*curr;

	curr = *head;
	while (curr)
	{
		if (curr->word->flags & W_EXPANDED)
		{
			identify_word_type(curr->word);
			if (curr->word->flags & (WM_REDIR_MASK | WM_OPERATOR_MASK))
			{
				if (!(curr->next))
					syntax_error(head, curr->word->word);
			}
		}
		curr = curr->next;
	}
	return (0);
}
