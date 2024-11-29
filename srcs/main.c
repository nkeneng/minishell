/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stevennkeneng <snkeneng@student.42ber      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 19:13:25 by stevennke         #+#    #+#             */
/*   Updated: 2024/11/29 10:48:36 by lmeubrin         ###   ########.fr       */
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
		line = rl_gets();
		if (!line)
			continue ;
		lst = parse_input(line, &shell);
		if (!lst)
			continue ;
		shell.exit_status = start_pipex(&lst, shell.envp);
		ft_lstclear(&lst, ft_free_command);
	}
	return (shell.exit_status);
}
