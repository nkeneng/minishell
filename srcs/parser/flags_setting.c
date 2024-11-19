/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags_setting.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeubrin <lmeubrin@student.42berlin.       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 17:13:11 by lmeubrin          #+#    #+#             */
/*   Updated: 2024/11/16 13:33:34 by lmeubrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//walks over word_list and sets the right flag on every word_desc item
void	assign_flag(t_word_list *list)
{
	t_word_list	*curr;
	int			flag;

	curr = list;
	flag = 0;
	while (curr)
	{
		flag = sign_to_flag(curr->word->word);
		if (flag & WM_OPERATOR_MASK)
			list = curr->next;
		else if (flag & WM_REDIR_MASK && curr->next)
			curr->next->word->flags |= flag;
		curr = curr->next;
	}
	assign_operator_till_end(list, W_LAST);
	return ;
}

void	assign_operator_till_end(t_word_list *list, int flag)
{
	int	end;

	end = 0;
	if (list)
		end = is_pipe_or_redirect(list->word->word);
	while (!(flag & end))
	{
		list->word->flags += flag;
		list = list->next;
		if (!list)
			break ;
		end = is_pipe_or_redirect(list->word->word);
	}
}
