/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stevennkeneng <snkeneng@student.42ber      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 19:13:25 by stevennke         #+#    #+#             */
/*   Updated: 2024/12/12 12:28:11 by lmeubrin         ###   ########.fr       */
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
	shell.exit_status = 0;
	init_envp(envp, &shell);
	while (1)
	{
		init_signals();
		if (g_signal)
		{
			shell.exit_status = (128 + g_signal);
			g_signal = 0;
		}
		line = rl_gets(PROMPT);
		if (!line)
			continue ;
		lst = parse_input(line, &shell);
		free(line);
		if (!lst)
			continue ;
		shell.exit_status = start_pipex(&lst, &shell);
		if (g_signal)
		{
			shell.exit_status = (128 + g_signal);
			if (g_signal == SIGINT)
				ft_printf("\n", 1);
			g_signal = 0;
		}
		init_signals_noninteractive();
		ft_lstclear(&lst, ft_free_command);
		if (g_signal == SIGINT)
			g_signal = 0;
	}
	return (shell.exit_status);
}
