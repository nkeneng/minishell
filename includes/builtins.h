/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stevennkeneng <snkeneng@student.42ber      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 21:02:38 by stevennke         #+#    #+#             */
/*   Updated: 2024/10/15 15:36:15 by stevennke        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"

int	ft_export(char **args, t_env **envp);
void	ft_override_env(char *key, char *value, t_env **envp);
int		ft_cd(char **cmd, t_env **envp);
int	ft_unset(char **args, t_env **envp);
int     ft_echo(char **args);
int	ft_exit(char **cmd);
int	ft_pwd(void);
int	ft_env(char **envp);
#endif
