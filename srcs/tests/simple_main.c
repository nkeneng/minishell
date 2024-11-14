/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeubrin <lmeubrin@student.42berlin.       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 10:02:32 by lmeubrin          #+#    #+#             */
/*   Updated: 2024/11/14 14:54:10 by lmeubrin         ###   ########.fr       */
/*   Updated: 2024/11/07 16:05:17 by lmeubrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_list		*lst;
	// char		line[] = "echo Hello >outfile.txt$hello >outfile2.txt < infile.txt|l\"s      |\"	 -e 	>file2.txt$$here 		| var=this";
	char line[] = " 	ls -l |   echo \"hello $USER\" 	| cat -e > toto";
	// int		exec_ret;
	ft_printf("line: %s\n", line);
	(void)argc;
	(void)argv;
	(void)envp;
	errno = 0;
	lst = parse_input(line, NULL);
	if (!lst)
		return (errno);
	ft_free_command_list(&lst);
	return (0);
}
