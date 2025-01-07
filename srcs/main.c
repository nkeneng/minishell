/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stevennkeneng <snkeneng@student.42ber      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 19:13:25 by stevennke         #+#    #+#             */
/*   Updated: 2025/01/07 18:00:05 by lmeubrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

volatile sig_atomic_t	g_signal = 0;

static void	handle_signals(t_shell *shell)
{
	if (g_signal)
	{
		shell->exit_status = (128 + g_signal);
		g_signal = 0;
	}
}

static void	process_line(char *line, t_shell *shell)
{
	t_list	*lst;

	lst = parse_input(line, shell);
	free(line);
	if (!lst)
		return ;
	shell->exit_status = start_pipex(&lst, shell);
	if (g_signal)
	{
		shell->exit_status = (128 + g_signal);
		if (g_signal == SIGINT)
			ft_printf("\n", 1);
		g_signal = 0;
	}
	init_signals_noninteractive();
	ft_lstclear(&lst, ft_free_command);
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
	init_envp(envp, &shell);
	while (!g_signal)
	{
		init_signals();
		handle_signals(&shell);
		line = rl_gets(PROMPT);
		if (!line)
			continue ;
		process_line(line, &shell);
	}
	ft_free_shell(&shell);
	return (shell.exit_status);
}
