/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stevennkeneng <snkeneng@student.42ber      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 12:56:57 by stevennke         #+#    #+#             */
/*   Updated: 2025/01/09 18:36:57 by lmeubrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_exit(char **cmd, t_shell *shell)
{
	int exit_code;
	char *endptr;

	exit_code = 0;
	(void)shell;
	if (cmd && cmd[1])
	{
		errno = 0;
		exit_code = ft_strtoimax(cmd[1], &endptr, 10);
		if (errno != 0 || *endptr != '\0')
		{
			ft_fprintf(2, "minishell: exit: %s: ", cmd[1]);
			ft_fprintf(2, "numeric argument required\n", cmd[1]);
			exit_code = 2;
			clean_exit(exit_code, shell);
		}
		else if (cmd[2])
		{
			ft_fprintf(2, "minishell: exit: too many arguments\n");
			return (1);
		}
	}
	clean_exit(exit_code, shell);
	exit(exit_code);
}