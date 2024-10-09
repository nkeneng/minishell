/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stevennkeneng <snkeneng@student.42ber      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 19:13:25 by stevennke         #+#    #+#             */
/*   Updated: 2024/10/09 11:52:21 by lmeubrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_list	*args;
	char	*line;
	int		num;
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
		num = ft_lstsize(args);
		exec_ret = do_list(&args, envp);
	}
	ft_lstclear(&args, 0);
	return (exec_ret);
}
