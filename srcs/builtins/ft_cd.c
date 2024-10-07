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
int	ft_cd(char *path)
{
	char	*home;

	if (!path)
	{
		home = getenv("HOME");
		if (!home)
		{
			perror("HOME not set");
			return (-1);
		}
		chdir(getenv("HOME"));
	}
	else if (chdir(path) == -1)
	{
		perror("chdir");
		return (-1);
	}
	return (1);
}
