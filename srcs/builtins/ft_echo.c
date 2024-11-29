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
 * @param n: A flag to determine whether 
 * a newline character should be printed at the end. 
 * If n is 0, a newline character is printed.
 *
 */
int	ft_echo(char **args, int n)
{
	int	i;

	if (n)
		i = 2;
	else
		i = 1; 
	while (args[i])
	{
		ft_putstr_fd(args[i], STDOUT_FILENO);
		if (args[i + 1])
			ft_putchar_fd(' ', STDOUT_FILENO);
		i++;
	}
	if (!n)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (EXIT_SUCCESS);
}
