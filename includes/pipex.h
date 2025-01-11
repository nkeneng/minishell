/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 05:10:36 by admin             #+#    #+#             */
/*   Updated: 2025/01/11 05:10:37 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "minishell.h"

// pipex_exec.c
int		exec_to_stdout(t_shell *shell, t_command *cmd, int chld_pids,
			int prev_fd);
int		handle_in_redirects(t_shell *shell, t_command *cmd, int *pipefd,
			int *prev_fd);
int		fork_child(t_shell *shell, t_command *cmd, int prev_fd, int *pipefd);

// pipex_core.c
void	pipex_child(t_command *cmd, int prev_fd, int *pipefd, t_shell *shell);
int		setup_pipfd(int (*pipefd)[2], int prev_fd);
int		pipex(t_shell *shell, t_list **cmd_list);
void	handle_child_input(t_shell *shell, t_command *cmd, int prev_fd,
			int *pipefd);
void	handle_child_exec(t_shell *shell, t_command *cmd, t_env **envp);

#endif
