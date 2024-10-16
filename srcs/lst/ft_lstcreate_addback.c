/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstcreate_addback.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeubrin <lmeubrin@student.42berlin.       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 12:05:56 by lmeubrin          #+#    #+#             */
/*   Updated: 2024/10/16 16:49:42 by lmeubrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_list	*ft_lstcreateaddback(t_list **lst, void *content)
{
	t_list	*node;

	node = ft_lstnew(content);
	if (!node)
	{
		free(node);
		return (NULL);
	}
	ft_lstadd_back(lst, node);
	return (node);
}
