/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stevennkeneng <snkeneng@student.42ber      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 12:56:57 by stevennke         #+#    #+#             */
/*   Updated: 2025/02/03 13:13:48 by lmeubrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_exit(char **cmd, t_shell *shell)
{
	int		exit_code;
	char	*endptr;

	exit_code = 0;
	(void)shell;
	if (cmd && cmd[1])
	{
		errno = 0;
		exit_code = ft_strtoimax(cmd[1], &endptr, 10);
		if (errno != 0 || *endptr != '\0')
		{
			ft_fprintf(2, "minishell: exit: %s: ", cmd[1]);
			ft_fprintf(2, "numeric argument required\n");
			exit_code = 2;
			clean_exit(exit_code, shell);
		}
		if (cmd[2])
		{
			ft_fprintf(2, "minishell: exit: too many arguments\n");
			return (1);
		}
	}
	clean_exit(exit_code, shell);
	exit(exit_code);
}
