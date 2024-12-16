/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stevennkeneng <snkeneng@student.42ber      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 12:58:38 by stevennke         #+#    #+#             */
/*   Updated: 2024/10/15 14:22:16 by stevennke        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * Function: ft_echo
 * -----------------
 * Implements the echo command in the shell.
 *
 * @param args: A null-terminated array of strings 
 * where each string is an argument to the echo command.
 *
 * The function handles multiple `-n` arguments and treats them as one.
 * If any character other than `n` is found after the initial `-`, 
 * the argument is treated as a regular argument.
 *
 * If no `-n` argument is found, a newline character is printed at the end.
 *
 * @return: Always returns EXIT_SUCCESS.
 */
int	ft_echo(char **args)
{
	int	i;
	int j;
	int to_print;

	i = 1; 
	to_print = 1;
	while (args[i])
	{
		if (args[i][0] == '-')
		{
			j = 1;
			while (args[i][j] == 'n')
				j++;
			if (args[i][j] == '\0')
			{
				to_print = 0;
				i++;
				continue;
			}
		}
		break;
	}
	while (args[i])
	{
		ft_putstr_fd(args[i], STDOUT_FILENO);
		if (args[i + 1])
			ft_putchar_fd(' ', STDOUT_FILENO);
		i++;
	}
	if (to_print)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (EXIT_SUCCESS);
}
