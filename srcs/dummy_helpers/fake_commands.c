/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fake_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stevennkeneng <snkeneng@student.42ber      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 15:54:33 by stevennke         #+#    #+#             */
/*   Updated: 2024/10/02 16:32:30 by stevennke        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	dummy_cmd_list(t_list **cmd_list)
{
	t_command	*cmd1;
	t_command	*cmd2;
	t_command	*cmd3;
	t_command	*cmd4;
	t_command	*cmd5;

	*cmd_list = NULL;
	cmd1 = ft_calloc(1, sizeof(t_command));
	cmd2 = ft_calloc(1, sizeof(t_command));
	cmd3 = ft_calloc(1, sizeof(t_command));
	cmd4 = ft_calloc(1, sizeof(t_command));
	cmd5 = ft_calloc(1, sizeof(t_command));
	cmd1->cmd = ft_strdup("ls -l");
	cmd2->cmd = ft_strdup("grep .c");
	cmd3->cmd = ft_strdup("wc -l");
	cmd4->cmd = ft_strdup("sort -r");
	cmd5->cmd = ft_strdup("cat -e");
	ft_lstadd_back(cmd_list, ft_lstnew(cmd1));
	ft_lstadd_back(cmd_list, ft_lstnew(cmd2));
	ft_lstadd_back(cmd_list, ft_lstnew(cmd3));
	ft_lstadd_back(cmd_list, ft_lstnew(cmd4));
	ft_lstadd_back(cmd_list, ft_lstnew(cmd5));
}
