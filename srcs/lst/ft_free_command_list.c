/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_command_list.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeubrin <lmeubrin@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 14:28:49 by lmeubrin          #+#    #+#             */
/*   Updated: 2025/02/03 19:49:23 by lmeubrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_free_command_list(t_list **lst)
{
	t_list	*tmp;

	if (!lst)
		return ;
	if (!*lst)
		return ;
	tmp = *lst;
	while (*lst)
	{
		ft_free_command(tmp->content);
		tmp = (*lst)->next;
		free(*lst);
		*lst = tmp;
	}
	return ;
}
