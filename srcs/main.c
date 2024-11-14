/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stevennkeneng <snkeneng@student.42ber      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 19:13:25 by stevennke         #+#    #+#             */
/*   Updated: 2024/11/14 12:26:49 by lmeubrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
		/* word_list_head = make_word_list_new(line); */
		/* ft_printf_word_list(word_list_head); */
		/* lst = convert_to_command_lst(word_list_head); */
		/* ft_printf_lst(lst, ft_printf_command); */
		/* free_word_list(&word_list_head); */
		lst = parse_input(line, &shell);
		if (!lst)
			continue ;
		start_pipex(&lst, envp);
		ft_lstclear(&lst, ft_free_command);
		// exec_ret = do_list(&wordlist, envp);
	}
	return (0);
	// return (exec_ret);
}
