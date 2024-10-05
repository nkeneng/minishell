/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stevennkeneng <snkeneng@student.42ber      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 21:02:38 by stevennke         #+#    #+#             */
/*   Updated: 2024/10/05 13:02:41 by stevennke        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_cd(char *path);
void	ft_unset(char **envp, char *key);
void	ft_echo(char **args);
void	ft_exit(void);
void	ft_pwd(void);
void	ft_env(char **envp);
