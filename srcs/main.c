/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stevennkeneng <snkeneng@student.42ber      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 19:13:25 by stevennke         #+#    #+#             */
/*   Updated: 2024/11/26 12:24:05 by lmeubrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_list		*lst;
	char	*line;
	t_shell	shell;
	struct sigaction sa;

	(void)argc;
	(void)argv;
	shell.envp = NULL;
	init_envp(envp, &shell);
	signals(&sa);
	while (1)
	{
		line = rl_gets();
		lst = parse_input(line, &shell);
		if (!lst)
			continue ;
		// shell.exit_status = start_pipex(&lst, envp);
		ft_lstclear(&lst, ft_free_command);
	}
	return (0);
	// return (shell.exit_status);
}
