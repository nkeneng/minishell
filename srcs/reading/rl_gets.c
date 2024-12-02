/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl_gets.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeubrin <lmeubrin@student.42berlin.       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 13:47:30 by lmeubrin          #+#    #+#             */
/*   Updated: 2024/12/01 16:46:08 by lmeubrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// input promt for shell
char	*rl_gets(void)
{
	static char	*line;

	// rl_catch_signals = 1;
	line = readline("〘🐚〙: ");
	if (!line)
		exit (0);
	// if (g_signal)
	// {
	// 	g_signal = 0;
	// 	return (line);
	// }
	// if (ft_strncmp("exit", line, 5) == 0)
	// 	exit (0);
	if (*line) // seeing if line is not is unnecessary because auf previous check, leaving it in for later
		add_history(line);
	return (line);
}
