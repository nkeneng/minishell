/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stevennkeneng <snkeneng@student.42ber      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 20:56:30 by stevennke         #+#    #+#             */
/*   Updated: 2024/10/02 22:05:10 by stevennke        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// TODO: update the PWD environment variable
// TODO: update the OLDPWD environment variable before changing cwd
// TODO: handle previous directory ( - )
int	ft_cd(char **cmd)
{
	char	*home;

	if (cmd && cmd[1] && cmd[2])
	{
		ft_printf("cd: too many arguments\n");
		return (EXIT_FAILURE);
	}
	if (cmd && !cmd[1])
	{
		home = getenv("HOME");
		if (!home)
		{
			perror("HOME not set");
			return (EXIT_FAILURE);
		}
		chdir(getenv("HOME"));
	}
	else if (chdir(cmd[1]) == -1)
	{
		perror("chdir");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
