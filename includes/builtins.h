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

int		ft_cd(char *path);
void	ft_unset(char **args, t_env **envp);
void	ft_echo(char **args, int n);
void	ft_exit(void);
void	ft_pwd(void);
void	ft_env(char **envp);
void	ft_export(char **args, t_env **envp);
#endif
