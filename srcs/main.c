/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stevennkeneng <snkeneng@student.42ber      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 19:13:25 by stevennke         #+#    #+#             */
/*   Updated: 2025/01/31 10:46:52 by lmeubrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

volatile sig_atomic_t	g_signal = 0;

static void	handle_signals(t_shell *shell)
{
	if (g_signal)
	{
		shell->exit_status = (128 + g_signal);
		if (g_signal == SIGQUIT)
			ft_free_shell(&shell);
		g_signal = 0;
	}
}

static void	process_line(char *line, t_shell *shell)
{
	t_list	*lst;

	lst = parse_input(line, shell);
	free(line);
	if (!lst)
	{
		shell->exit_status = errno;
		return ;
	}
	shell->cmds = &lst;
	shell->exit_status = start_pipex(&lst, shell);
	handle_signals(shell);
	init_signals_noninteractive();
	ft_lstclear(&lst, ft_free_command);
	shell->cmds = NULL;
	if (g_signal == SIGINT)
		g_signal = 0;
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	t_shell	shell;

	(void)argc;
	(void)argv;
	shell.envp = NULL;
	shell.exit_status = 0;
	shell.cmds = NULL;
	init_envp(envp, &shell);
	while (1)
	{
		init_signals();
		handle_signals(&shell);
		line = rl_gets(PROMPT, &shell);
		if (!line)
			continue ;
		handle_signals(&shell);
		process_line(line, &shell);
	}
	if (shell.envp)
		ft_free_envp(shell.envp);
	return (shell.exit_status);
}
