/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_word_list_to_list.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeubrin <lmeubrin@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 11:14:56 by lmeubrin          #+#    #+#             */
/*   Updated: 2024/11/06 11:15:00 by lmeubrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_list	*convert_word_list_to_list(t_word_list *word_list)
{
	t_list		*lst;
	// t_command	*command;
	t_word_list	*curr;
	t_list		*redirect_list;

	lst = NULL;
	curr = word_list;
	// while (curr)
	// {
		redirect_list = make_redirect_list(&curr);
		// command = make_command_list(word_list, curr);
		// command->redirects = redirect_list;
		ft_printf_lst(redirect_list, ft_printf_word_desc);
		// ft_lstadd_back(&lst, ft_lstnew(command));
	ft_printf_word_list(word_list);
	// }
	return (lst);
}
