/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_redirection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeubrin <lmeubrin@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 12:06:49 by lmeubrin          #+#    #+#             */
/*   Updated: 2024/12/20 13:17:49 by lmeubrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// checks if the redirects list of the command contains a file with the 
// given flags
int has_flags(t_command *command, int wordmask_in_or_out)
{
	t_list		*redir_list;
	t_redirect	*redir;

	redir_list = command->redirects;
	while (redir_list && redir_list->content && !g_signal)
	{
		redir = redir_list->content;
		if (redir->filename->flags & wordmask_in_or_out)
			return (1);
		redir_list = redir_list->next;
	}
	return (0);
}

// calls open_doc over redirect list
// when given C_OPEN_INFILE | C_HERE_DOC dups over STDIN_FILENO
// when given C_OPEN_OUT_TRUNC | C_OPEN_OUT_APP dups over STDOUT_FILENO
int	handle_redirects(t_shell *shell, t_command *command, int wordmask_in_or_out)
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
			status = open_doc(shell, redir->filename->word, redir->filename->flags);
			if (status || g_signal)
				return (status);
		}
		redir_list = redir_list->next;
	}
	return (0);
}

void	reopen_stdin(void)
{
	if (isatty(STDIN_FILENO))
		return ;
	close(STDIN_FILENO);
	if (open("/dev/tty", O_RDONLY) != STDIN_FILENO)
	{
		perror("Failed to reopen stdin");
		exit(EXIT_FAILURE);
	}
}

void	reopen_stdout(void)
{
	if (isatty(STDOUT_FILENO))
		return ;
	close(STDOUT_FILENO);
	if (open("/dev/tty", O_WRONLY) != STDOUT_FILENO)
	{
		perror("Failed to reopen stdout");
		exit(EXIT_FAILURE);
	}
}
