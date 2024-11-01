/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeubrin <lmeubrin@student.42berlin.       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 10:49:46 by lmeubrin          #+#    #+#             */
/*   Updated: 2024/11/01 18:41:46 by lmeubrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// apply cleaning of whitespace on lst
void	wl_clean_whitespace(t_word_list *lst)
{
	while (lst)
	{
		clean_line_whitespace(lst->word);
		lst = lst->next;
	}
}
//if not in quotes: deletes multiple spaces and converts tabs to single space
void	clean_line_whitespace(t_word_desc *obj)
{
	int	i;
	int	j;
	int	len;

	if (obj->flags & W_DQUOTED || obj->flags & W_SQUOTED)
		return ;
	i = 0;
	len = ft_strlen(obj->word);
	if (len > 0 && obj->word[len - 1] == '\n')
		obj->word[len - 1] = '\0';
	while (obj->word[i])
	{
		j = i;
		if (obj->word[i] == '\t')
			obj->word[i] = ' ';
		while (obj->word[j] == ' ' || obj->word[j] == '\t')
			j++;
		if (j > i + 1)
			ft_memmove(obj->word + i, obj->word + j, ft_strlen(obj->word + i));
		i++;
	}
}
