/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags_setting.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeubrin <lmeubrin@student.42berlin.       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 17:13:11 by lmeubrin          #+#    #+#             */
/*   Updated: 2024/11/01 18:44:14 by lmeubrin         ###   ########.fr       */
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
		if (flag & W_DQUOTED || flag & W_SQUOTED)
			curr->word->flags = flag;
		else
		{
			curr->word->flags = flag;
			if (flag & W_ASSIGNMENT)
			{
				curr->next->word->flags = flag;
				curr->prev->word->flags = flag;
			}
			else if (flag & W_VAR)
				curr->next->word->flags = flag;
			else
			{
				assign_operator_till_end(list, flag);
				list = curr;
			}
		}
		curr = curr->next;
	}
	assign_operator_till_end(list, W_LAST);
	return ;
}

void	assign_operator_till_end(t_word_list *list, int flag)
{
	int	end;

	end = is_pipe_or_redirect(list->word->word);
	while (list && !(WM_OPERATOR_MASK & end))
	{
		list->word->flags &= flag;
		list = list->next;
	}
}
