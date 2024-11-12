/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_word_list_to_list.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeubrin <lmeubrin@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 11:14:56 by lmeubrin          #+#    #+#             */
/*   Updated: 2024/11/10 14:33:55 by lmeubrin         ###   ########.fr       */
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
		command = make_command_list(&word_list);
		ft_lstadd_back(&lst, ft_lstnew(command));
		ft_printf("command found : \n ");
		ft_printf_command(command);
	}
	return (lst);
}
