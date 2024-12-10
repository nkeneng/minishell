/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_word_list_to_list.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeubrin <lmeubrin@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 11:14:56 by lmeubrin          #+#    #+#             */
/*   Updated: 2024/12/10 17:08:24 by lmeubrin         ###   ########.fr       */
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
	while (word_list)
	{
		redirect_list = make_redirect_list(&word_list);
		if (!redirect_list && !word_list)
			return (NULL);
		command = make_command_list(&word_list);
		if (!command)
		{
			if (redirect_list)
				ft_printf("minishell: %s: no such file or directory\n", \
			((t_redirect *)redirect_list->content)->filename->word);
			ft_lstclear(&redirect_list, ft_free_redirect);
			ft_lstclear(&lst, ft_free_command);
			return (NULL);
		}
		if (redirect_list)
			command->redirects = redirect_list;
		ft_lstadd_back(&lst, ft_lstnew(command));
	}
	return (lst);
}
