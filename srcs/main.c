/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stevennkeneng <snkeneng@student.42ber      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 19:13:25 by stevennke         #+#    #+#             */
/*   Updated: 2024/10/22 15:53:06 by stevennke        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_list	*tmp;
	t_shell	shell;
	t_list *cmd_list;
	int		i;

	(void)argc;
	(void)argv;
	(void)shell;
	(void)tmp;
	(void)i;
	i = 0;
	shell.envp = NULL;
	init_envp(envp, &shell);
	start_pipex(&cmd_list, envp);
	return (EXIT_SUCCESS);
}
