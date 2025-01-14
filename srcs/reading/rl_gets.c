/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl_gets.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeubrin <lmeubrin@student.42berlin.       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 13:47:30 by lmeubrin          #+#    #+#             */
/*   Updated: 2025/01/14 16:06:00 by lmeubrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <unistd.h>

// input promt for shell
char	*rl_gets(char *prompt, t_shell *shell)
{
	static char	*line;

	line = readline(prompt);
	if (!line)
		clean_exit (0, shell);
	if (*line)
		add_history(line);
	return (line);
}
