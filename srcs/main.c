/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stevennkeneng <snkeneng@student.42ber      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 19:13:25 by stevennke         #+#    #+#             */
/*   Updated: 2024/12/02 16:07:53 by lmeubrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <fcntl.h>
#include <unistd.h>

volatile sig_atomic_t	g_signal = 0;

int	main(int argc, char **argv, char **envp)
{
	t_list				*lst;
	char				*line;
	t_shell				shell;

	(void)argc;
	(void)argv;
	shell.envp = NULL;
	init_envp(envp, &shell);
	init_signals();
	// signal(SIGINT, signal_handler);
	// signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		if (g_signal)
		{
			shell.exit_status = (128 + g_signal);
			g_signal = 0;
		}
		line = rl_gets();
		if (!line)
			continue ;
		lst = parse_input(line, &shell);
		free(line);
		if (!lst)
			continue ;
		// signal(SIGINT, SIG_IGN);
		shell.exit_status = start_pipex(&lst, &(shell.envp));
		if (g_signal)
		{
			shell.exit_status = (128 + g_signal);
			if (g_signal == SIGINT)
				ft_printf("\n", 1);
			g_signal = 0;
		}
		init_signals();
		ft_lstclear(&lst, ft_free_command);
	}
	return (shell.exit_status);
}
