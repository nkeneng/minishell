/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_main_for_list.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeubrin <lmeubrin@student.42berlin.       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 10:02:32 by lmeubrin          #+#    #+#             */
/*   Updated: 2024/11/07 16:05:17 by lmeubrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_word_list	*word_list_head;
	// t_list		*lst;
	// char		line[] = "echo Hello >outfile.txt$hello >outfile2.txt < infile.txt|l\"s      |\"	 -e 	>file2.txt$$here 		| var=this";
	char line[] = "ls -l | cat -e > toto";
	// int		exec_ret;
	ft_printf("line: %s\n", line);
	(void)argc;
	(void)argv;
	(void)envp;
	errno = 0;
	word_list_head = make_word_list(line);
	if (!word_list_head)
		return (errno);
	// ft_printf_word_list(word_list_head);
	convert_word_list_to_list(word_list_head);
	// lst = convert_to_command_lst(word_list_head);
	// ft_printf_lst(lst, ft_printf_command);
	// free_word_list(&word_list_head);
	// ft_lstclear(&lst, ft_free_command);
	// exec_ret = do_list(&wordlist, envp);
	return (0);
	// return (exec_ret);
}
