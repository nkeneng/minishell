/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl_gets.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeubrin <lmeubrin@student.42berlin.       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 13:47:30 by lmeubrin          #+#    #+#             */
/*   Updated: 2024/11/29 10:14:02 by lmeubrin         ###   ########.fr       */
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
	line = readline("〘🐚〙: ");
	if (!line)
		exit (0);
	if (ft_strncmp("exit", line, 4) == 0)
		exit (0);
	if (line && *line) // seeing if line is not is unnecessary because auf previous check, leaving it in for later
		add_history(line);
	return (line);
}
