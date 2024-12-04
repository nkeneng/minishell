/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_redirects.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeubrin <lmeubrin@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 11:44:12 by lmeubrin          #+#    #+#             */
/*   Updated: 2024/12/04 13:38:40 by lmeubrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_lstfreeone(t_list **lst, t_list *deletee, void (*free_cont)(void *))
{
	if (!lst || !deletee)
		return ;
	if (*lst == deletee)
		*lst = deletee->next;
	if (deletee->content)
		free_cont(deletee->content);
	free(deletee);
	return ;
}

void	ft_free_redirect(void *redirict)
{
	t_redirect	*redir;

	redir = (t_redirect *)redirict;
	if (redir)
	{
		if (redir->filename)
			free_word_desc(&redir->filename);
		free(redir);
	}
	return ;
}
