/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeubrin <lmeubrin@student.42berlin.       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 12:39:22 by lmeubrin          #+#    #+#             */
/*   Updated: 2024/11/27 14:53:37 by lmeubrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_free_command(void *command)
{
	t_command	*com;

	com = (t_command *) command;
	ft_lstclear(&(com->redirects), ft_free_word_desc);
	free_char_array(com->cmd, 0);
	free(com);
	return ;
}
