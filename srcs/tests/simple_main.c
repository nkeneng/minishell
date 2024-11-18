/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeubrin <lmeubrin@student.42berlin.       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 10:02:32 by lmeubrin          #+#    #+#             */
/*   Updated: 2024/11/18 10:15:40 by lmeubrin         ###   ########.fr       */
/*   Updated: 2024/11/07 16:05:17 by lmeubrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_list		*lst;
	// char		line[] = "echo Hello >outfile.txt$hello >outfile2.txt < infile.txt|l\"s      |\"	 -e 	>file2.txt$$here 		| var=this";
	t_shell		*shell;
	char	line[] = "echo $USER | ls -l >outfile.txt";
	// char line[] = " 	ls -l$A# |   echo \"hello $USER\" 	| cat -e > toto";
	// int		exec_ret;
	ft_printf("line: %s\n", line);
	(void)argc;
	(void)argv;
	(void)envp;
	errno = 0;
	shell = init_shell(envp);
	lst = parse_input(line, shell);
	if (!lst)
		return (errno);
	ft_free_command_list(&lst);
	ft_free_shell(&shell);
	return (0);
}
