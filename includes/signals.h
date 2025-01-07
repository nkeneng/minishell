/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 14:34:04 by admin             #+#    #+#             */
/*   Updated: 2025/01/07 14:41:25 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

# include "minishell.h"

void	signal_handler_heredoc(int signum);
void	init_signals_heredoc(void);
void	signal_print_newline(int signum);
void	init_signals(void);
void	signal_dfl(int signum);
void	signal_ign(int signum);

#endif
