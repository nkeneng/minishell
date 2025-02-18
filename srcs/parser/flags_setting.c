/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags_setting.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeubrin <lmeubrin@student.42berlin.       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 17:13:11 by lmeubrin          #+#    #+#             */
/*   Updated: 2025/02/01 09:02:00 by lmeubrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//walks over word_list and sets the right flag on every word_desc item
void	assign_flag(t_word_list *list)
{
	t_word_list	*curr;
	int			flag;
	int			pipenumber;

	curr = list;
	flag = 0;
	pipenumber = 0;
	while (curr)
	{
		flag = sign_to_flag(curr->word->word);
		if (flag & WM_OPERATOR_MASK && \
			curr->word->flags != W_DQUOTED && curr->word->flags != W_SQUOTED)
		{
			list = curr->next;
			pipenumber++;
		}
		curr = curr->next;
	}
	if (pipenumber == 1)
		assign_operator_till_end(list, W_ONLY);
	else
		assign_operator_till_end(list, W_LAST);
	return ;
}

void	assign_operator_till_end(t_word_list *list, int flag)
{
	int	end;

	end = 0;
	if (list)
		end = is_pipe_or_redirect(list->word->word);
	while (!(flag & end))
	{
		list->word->flags += flag;
		list = list->next;
		if (!list)
			break ;
		end = is_pipe_or_redirect(list->word->word);
	}
}

int	is_builtin(char *command)
{
	if (command[0] == 'e')
	{
		if (command[1] == 'x')
		{
			if (ft_strncmp(&command[2], "it", 2) == 0 && !command[4])
				return (EXIT_BUILTIN);
			if (ft_strncmp(&command[2], "port", 4) == 0 && !command[6])
				return (EXPORT_BUILTIN);
		}
		else if (command[1] == 'n')
		{
			if (ft_strncmp(&command[2], "v", 1) == 0 && !command[3])
				return (ENV_BUILTIN);
		}
		else if (command[1] == 'c')
			if (ft_strncmp(&command[2], "ho", 2) == 0 && !command[4])
				return (ECHO_BUILTIN);
	}
	else if (ft_strncmp(command, "pwd", 3) == 0 && !command[3])
		return (PWD_BUILTIN);
	else if (ft_strncmp(command, "unset", 5) == 0 && !command[5])
		return (UNSET_BUILTIN);
	else if (ft_strncmp(command, "cd", 2) == 0 && !command[2])
		return (CD_BUILTIN);
	return (0);
}
