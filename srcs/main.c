/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stevennkeneng <snkeneng@student.42ber      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 19:13:25 by stevennke         #+#    #+#             */
/*   Updated: 2024/10/08 16:31:08 by lmeubrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	/* t_list	**split_line; */
	t_list	*args;
	/* char	*line; */
	/* int		num; */
	int		exec_ret;

	(void)argc;
	(void)argv;
	(void)envp;
	/* while (1) */
	/* { */
		/* line = rl_gets(); */
		/* split_line = parse_input(line, envp); */
		/* num = ft_lstsize(*split_line); */
		/* exec_ret = do_list(split_line, envp); */
	/* } */
	exec_ret = do_list(&args, envp);
	ft_lstclear(&args, 0);
	return (exec_ret);
}
