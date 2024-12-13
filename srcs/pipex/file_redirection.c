/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_redirection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeubrin <lmeubrin@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 12:06:49 by lmeubrin          #+#    #+#             */
/*   Updated: 2024/12/13 10:05:17 by lmeubrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// calls open_doc over redirect list
// when given C_OPEN_INFILE | C_HERE_DOC dups over STDIN_FILENO
// when given C_OPEN_OUT_TRUNC | C_OPEN_OUT_APP dups over STDOUT_FILENO
int	handle_redirects(t_command *command, int wordmask_in_or_out)
{
	t_list		*redir_list;
	t_redirect	*redir;
	int			status;

	redir_list = command->redirects;
	while (redir_list && redir_list->content && !g_signal)
	{
		redir = redir_list->content;
		if (redir->filename->flags & wordmask_in_or_out)
		{
			status = open_doc(redir->filename->word, redir->filename->flags);
			if (status || g_signal)
				return (status);
		}
		redir_list = redir_list->next;
	}
	return (0);
}
