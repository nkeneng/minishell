/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stevennkeneng <snkeneng@student.42ber      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 15:33:15 by stevennke         #+#    #+#             */
/*   Updated: 2025/01/09 17:52:20 by lmeubrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "minishell.h"

typedef struct s_env
{
	char			*key;
	char			*value;
}					t_env;

typedef struct s_shell
{
	t_env			*envp;
	int				nb_env;
	int				exit_status;
	t_list			**cmds;
}					t_shell;

typedef struct s_dlist
{
	char			*content;
	struct s_dlist	*next;
	struct s_dlist	*prev;
}					t_dlist;

#endif
