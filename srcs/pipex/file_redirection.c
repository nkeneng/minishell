/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_redirection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeubrin <lmeubrin@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 12:06:49 by lmeubrin          #+#    #+#             */
/*   Updated: 2024/12/03 12:07:14 by lmeubrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_redirect_in(t_command *command)
{
	t_redirect	*redir;
	t_redirect	*tmp;

	redir = command->redirects->content;
	while (command->redirects)
	{
		tmp = redir;
		if (redir->filename->flags & W_OPEN_INFILE || redir->filename->flags & W_HERE_DOC)
		{
			printf("opening input file %s\n", redir->filename->word);
			open_doc(redir->filename->word, redir->filename->flags);
		}
		redir = redir->next;
		ft_lstfreeone(&command->redirects, (void *) tmp, ft_free_redirect);
	}
}

void	handle_redirect_out(t_command *command)
{
	t_redirect	*redir;
	t_redirect	*tmp;

	redir = command->redirects->content;
	while (command->redirects)
	{
		tmp = redir;
		if (redir->filename->flags & W_OPEN_OUT_TRUNC || redir->filename->flags & W_OPEN_OUT_APP)
		{
			printf("opening output file %s\n", redir->filename->word);
			open_doc(redir->filename->word, redir->filename->flags);
		}
		redir = redir->next;
		ft_lstfreeone(&command->redirects, (void *) tmp, ft_free_redirect);
	}
}
