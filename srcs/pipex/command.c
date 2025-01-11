/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeubrin <lmeubrin@student.42berlin.       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 15:42:30 by lmeubrin          #+#    #+#             */
/*   Updated: 2025/01/10 16:11:25 by lmeubrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * Helper that handles a single segment of the pipeline.
 * Returns:
 *   2 if we need to skip the fork and move on,
 *   EXIT_FAILURE on error,
 *   0 otherwise.
 */
static int	handle_pipe_segment(t_shell *shell, t_command *cmd, int *pipefd,
		int *prev_fd)
{
	if (handle_in_redirects(shell, cmd, pipefd, prev_fd))
		return (2);
	if (fork_child(shell, cmd, *prev_fd, pipefd) == -1)
		return (EXIT_FAILURE);
	close(pipefd[1]);
	if (*prev_fd != -1)
		close(*prev_fd);
	*prev_fd = pipefd[0];
	init_signals_when_children();
	return (0);
}

int	pipex(t_shell *shell, t_list **cmd_list)
{
	int		ret;
	int		pipefd[2];
	int		p_nb;
	int		prev_fd;
	t_list	*tmp_list;

	tmp_list = *cmd_list;
	prev_fd = -1;
	p_nb = ft_lstsize(*cmd_list);
	init_signals_when_children();
	while (tmp_list->next)
	{
		ret = handle_pipe_segment(shell, tmp_list->content, pipefd, &prev_fd);
		if (ret == 2)
		{
			tmp_list = tmp_list->next;
			continue ;
		}
		if (ret == EXIT_FAILURE)
			return (EXIT_FAILURE);
		tmp_list = tmp_list->next;
	}
	return (exec_to_stdout(shell, ft_lstlast(*cmd_list)->content, p_nb,
			prev_fd));
}
