/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stevennkeneng <snkeneng@student.42ber      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 12:56:57 by stevennke         #+#    #+#             */
/*   Updated: 2025/01/07 17:02:18 by lmeubrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_exit(char **cmd, t_list **cmd_list)
{
	int		exit_code = 0;
	char	*endptr;

	if (cmd && cmd[1])
	{
		if (cmd[2])
		{
			ft_fprintf(2, "minishell: exit: too many arguments\n");
			return (1);
		}
		errno = 0;
		exit_code = ft_strtoimax(cmd[1], &endptr, 10);
		if (errno != 0 || *endptr != '\0')
		{
			ft_fprintf(2, "minishell: exit: %s: numeric argument required\n", cmd[1]);
			exit_code = 2;
			ft_lstclear(cmd_list, ft_free_command);
			exit(exit_code);
		}
	}
	exit(exit_code);
}
