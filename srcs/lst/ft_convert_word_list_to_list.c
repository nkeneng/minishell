/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_word_list_to_list.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeubrin <lmeubrin@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 11:14:56 by lmeubrin          #+#    #+#             */
/*   Updated: 2024/11/16 12:52:36 by lmeubrin         ###   ########.fr       */
/*   Updated: 2024/11/06 16:22:55 by snkeneng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_list	*convert_word_list_to_list(t_word_list *word_list)
{
	t_list		*lst;
	t_list		*redirect_list;
	t_command	*command;

	lst = NULL;
	redirect_list = NULL;
	(void)command;
	(void)redirect_list;
	while (word_list)
	{
		redirect_list = make_redirect_list(&word_list);
		if (!redirect_list && !word_list)
			return (NULL);
		command = make_command_list(&word_list);
		if (redirect_list)
			command->redirects = redirect_list;
		// ft_printf_word_list(word_list);
		// if (!command)
		// ft_lstclear(&lst, free_command); // free_command is not implemented
		// command->redirects = redirect_list;
		// ft_printf_lst(redirect_list, ft_printf_redirect);
		// ft_lstadd_back(&lst, ft_lstnew(command));
		// ft_printf_word_list(word_list);
		// ft_printf_lst(redirect_list, ft_printf_word_desc);
		ft_lstadd_back(&lst, ft_lstnew(command));
	}
	return (lst);
}
