/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl_gets.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeubrin <lmeubrin@student.42berlin.       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 13:47:30 by lmeubrin          #+#    #+#             */
/*   Updated: 2024/10/08 13:47:51 by lmeubrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// input promt for shell
char	*rl_gets(void)
{
	static char	*line;

	if (line)
	{
		free(line);
		line = NULL;
	}
	line = readline("minishell$ ");
	if (!line)
	{
		ft_printf("exiting");
		exit (0);
	}
	if (ft_strncmp("exit", line, 4) == 0)
	{
		ft_printf("exiting strncmp");
		exit (0);
	}
	if (line && *line) // seeing if line is not is unnecessary because auf previous check, leaving it in for later
		add_history(line);
	return (line);
}
