/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stevennkeneng <snkeneng@student.42ber      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 19:13:25 by stevennke         #+#    #+#             */
/*   Updated: 2024/11/23 17:08:13 by lmeubrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <fcntl.h>
#include <unistd.h>

int	main(int argc, char **argv, char **envp)
{
	t_list		*lst;
	char	*line;
	t_shell	shell;
	// int		exec_ret;

	(void)argc;
	(void)argv;
	(void)envp;
	shell.envp = NULL;
	init_envp(envp, &shell);
	while (1)
	{
		line = rl_gets();
		lst = parse_input(line, &shell);
		if (!lst)
			continue ;
		// shell.exit_status = start_pipex(&lst, envp);
		ft_lstclear(&lst, ft_free_command);
		// exec_ret = do_list(&wordlist, envp);
	}
	return (0);
	// return (exec_ret);
}
