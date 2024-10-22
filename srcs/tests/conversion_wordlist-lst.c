/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversion_wordlist-lst.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeubrin <lmeubrin@student.42berlin.       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 17:43:42 by lmeubrin          #+#    #+#             */
/*   Updated: 2024/10/22 16:27:33 by lmeubrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	/* t_word_list	*word_list_head; */
	t_list		*lst;
	char	*line;
	// int		exec_ret;

	(void)argc;
	(void)argv;
	(void)envp;
	while (1)
	{
		line = rl_gets();
		/* word_list_head = make_word_list_new(line); */
		/* ft_printf_word_list(word_list_head); */
		/* lst = convert_to_command_lst(word_list_head); */
		/* ft_printf_lst(lst, ft_printf_command); */
		/* free_word_list(&word_list_head); */
		lst = parse_input(line, envp);
		start_pipex(&lst, envp);
		ft_lstclear(&lst, ft_free_command);
		// exec_ret = do_list(&wordlist, envp);
	}
	return (0);
	// return (exec_ret);
}
