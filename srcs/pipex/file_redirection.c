/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_redirection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeubrin <lmeubrin@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 12:06:49 by lmeubrin          #+#    #+#             */
/*   Updated: 2024/12/03 13:39:09 by lmeubrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_redirect_in(t_command *command)
{
	t_redirect	*tmp;
	t_list		*redir_list;
	t_redirect	*redir;

	redir_list = command->redirects;
	while (redir_list && redir_list->content)
	{
		tmp = redir;
		redir = redir_list->content;
		if (redir->filename->flags & C_OPEN_INFILE || redir->filename->flags & C_HERE_DOC)
		{
			printf("opening input file %s\n", redir->filename->word);
			open_doc(redir->filename->word, redir->filename->flags);
		// ft_lstfreeone(&command->redirects, (void *) tmp, ft_free_redirect);
		}
		redir_list = redir_list->next;
	}
}

void	handle_redirect_out(t_command *command)
{
	t_redirect	*tmp;
	t_list		*redir_list;
	t_redirect	*redir;

	redir_list = command->redirects;
	while (redir_list && redir_list->content)
	{
		tmp = redir;
		redir = redir_list->content;
		if (redir->filename->flags & W_OPEN_OUT_TRUNC || redir->filename->flags & W_OPEN_OUT_APP)
		{
			printf("opening output file %s\n", redir->filename->word);
			open_doc(redir->filename->word, redir->filename->flags);
		// ft_lstfreeone(&command->redirects, (void *) tmp, ft_free_redirect);
		}
		redir_list = redir_list->next;
	}
}

// calls open_doc over redirect list
// when given C_OPEN_INFILE | C_HERE_DOC dups over STDIN_FILENO
// when given C_OPEN_OUT_TRUNC | C_OPEN_OUT_APP dups over STDOUT_FILENO
void	handle_redirects_all(t_command *command, int wordmask_in_or_out)
{
	t_redirect	*tmp;
	t_list		*redir_list;
	t_redirect	*redir;

	redir_list = command->redirects;
	while (redir_list && redir_list->content)
	{
		tmp = redir;
		redir = redir_list->content;
		if (redir->filename->flags & wordmask_in_or_out)
		{
			if (open_doc(redir->filename->word, redir->filename->flags))
				return ;
		// ft_lstfreeone(&command->redirects, (void *) tmp, ft_free_redirect);
		}
		redir_list = redir_list->next;
	}
}
