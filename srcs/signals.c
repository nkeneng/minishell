/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeubrin <lmeubrin@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 12:19:29 by lmeubrin          #+#    #+#             */
/*   Updated: 2025/01/09 07:56:05 by lmeubrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <unistd.h>

// ignore SIGQUIT and SIGINT
void	init_signals_heredoc(void)
{
	struct sigaction	sa;

	ft_memset(&sa, 0, sizeof(sa));
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sa.sa_handler = SIG_IGN;
	if (sigaction(SIGQUIT, &sa, NULL) == -1)
		perror("Error: cannot handle SIGQUIT");
	if (sigaction(SIGINT, &sa, NULL) == -1)
		perror("Error: cannot handle SIGINT");
}

void	signal_handler_when_children(int signum)
{
	if (signum == SIGINT)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		g_signal = SIGINT;
	}
	if (signum == SIGQUIT)
	{
		write(STDERR_FILENO, "Quit (core dumped)\n", 20);
		g_signal = SIGQUIT;
	}
	return ;
}

void	init_signals_when_children(void)
{
	struct sigaction	sa;

	ft_memset(&sa, 0, sizeof(sa));
	sa.sa_handler = signal_handler_when_children;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	if (sigaction(SIGINT, &sa, NULL) == -1)
		perror("Error: cannot handle SIGINT");
	if (sigaction(SIGQUIT, &sa, NULL) == -1)
		perror("Error: cannot handle SIGQUIT");
}

void	signal_handler_noninteractive(int signum)
{
	if (signum == SIGINT)
		g_signal = SIGINT;
	if (signum == SIGQUIT)
		g_signal = SIGQUIT;
	return ;
}

void	init_signals_noninteractive(void)
{
	struct sigaction	sa;

	ft_memset(&sa, 0, sizeof(sa));
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sa.sa_handler = signal_handler_noninteractive;
	if (sigaction(SIGINT, &sa, NULL) == -1)
		perror("Error: cannot handle SIGINT");
	if (sigaction(SIGQUIT, &sa, NULL) == -1)
		perror("Error: cannot handle SIGQUIT");
}
