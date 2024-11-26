/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeubrin <lmeubrin@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 12:19:29 by lmeubrin          #+#    #+#             */
/*   Updated: 2024/11/26 13:56:59 by lmeubrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	signals(struct sigaction *sa)
{
	sa->sa_handler = &signal_handler;
	sigemptyset(&sa->sa_mask);
	if (sigaction(SIGINT, sa, NULL) == -1)
	{
		perror("Error: cannot handle SIGINT");
	}
	if (sigaction(SIGQUIT, sa, NULL) == -1)
	{
		perror("Error: cannot handle SIGQUIT");
	}
	if (sigaction(SIGCHLD, sa, NULL) == -1)
	{
		perror("Error: cannot handle SIGCHLD");
	}
	return (0);
}
