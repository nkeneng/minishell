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
 * Checks if the argument is a valid '-n' flag
 * Returns the next argument index and updates the newline printing flag
 */
static int	handle_n_flag(char **args, int *to_print)
{
	int	i;
	int	j;

	i = 1;
	while (args[i])
	{
		if (args[i][0] == '-')
		{
			j = 1;
			if (args[i][j] == '\0')
				return (i);
			while (args[i][j] == 'n')
				j++;
			if (args[i][j] == '\0')
			{
				*to_print = 0;
				i++;
				continue ;
			}
		}
		break ;
	}
	return (i);
}

int	ft_echo(char **args)
{
	int	i;
	int	to_print;

	to_print = 1;
	i = handle_n_flag(args, &to_print);
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
