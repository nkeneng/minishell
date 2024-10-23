/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeubrin <lmeubrin@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 15:55:44 by lmeubrin          #+#    #+#             */
/*   Updated: 2024/10/23 14:55:43 by lmeubrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_printf_lst(t_list *lst, int (*print)(void*))
{
	int	i;
	int	count;

	i = 1;
	count = 0;
	while (lst)
	{
		ft_printf("%d:", i++);
		count += print(lst->content);
		lst = lst->next;
	}
	return (count);
}

int	ft_printf_command(void *command)
{
	t_command	*cmd;
	int			count;

	cmd = (t_command *) command;
	count = ft_printf_char_array(cmd->cmd);
	count += ft_printf("	%d\n", cmd->flags);
	if (cmd->redirects)
		count += ft_printf("	has redirects\n");
	count += ft_printf("\n");
	return (count);
}
