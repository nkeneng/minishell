/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stevennkeneng <snkeneng@student.42ber      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 19:13:25 by stevennke         #+#    #+#             */
/*   Updated: 2024/10/11 17:11:42 by lmeubrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_list	*args;
	char	*line;
	int		exec_ret;

	(void)argc;
	(void)argv;
	(void)envp;
	while (1)
	{
		line = rl_gets();
		//if (missing_close(line))
		//	append_line(line, rl_gets());
		args = parse_input(line, envp);
		if (args == NULL)
			ft_printf("has been freed");
		exec_ret = start_pipex(0, NULL, envp);
	}
	ft_lstclear(&args, 0);
	return (exec_ret);
}
